#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse, glob, os, random, shutil, subprocess, sys, thread, time
import pp

g_dir = 'experiment'
g_plotter = './puddleworld.py'

g_ep_tuples = []

g_ep_tuples.append(('puddle-world', 1.0, 0.1, 0.2, 'off-policy'))

parser = argparse.ArgumentParser(description='Run PuddleWorld experiments.')
parser.add_argument('-j', '--jobs', metavar='N', type=int,
                   action='store',
                   help='number of experiments to run in parallel')
parser.add_argument('-r', '--runs', metavar='N', type=int,
                   action='store', default=1,
                   help='number of runs per experiment')
parser.add_argument('-s', '--steps', metavar='N', type=int,
                   action='store', default=50000,
                   help='number of steps per run')

args = parser.parse_args()

if args.jobs is None:
  args.jobs = 'autodetect'


if not os.path.isdir(g_dir):
  os.mkdir(g_dir)
seeds = []
seeds_file = g_dir + '/seeds'
if os.path.isfile(seeds_file):
  f = open(seeds_file, 'r')
  for seed in f:
    seeds.append(int(seed))
  f.close()
if len(seeds) != args.runs:
  seeds = []
  for i in range(0, args.runs):
    seeds.append(random.randint(0,65535))
  f = open(seeds_file, 'w')
  for seed in seeds:
    f.write(str(seed) + '\n')
  f.close()
print str(seeds) + '\n'


class Experiment:
  def __init__(self, num_steps, seed, stderr, stdout, ep_tuple):
    self.num_steps = num_steps
    self.seed = seed
    self.stderr = stderr
    self.stdout = stdout
    self.ep_tuple = ep_tuple
    self.environment = ep_tuple[0]
    self.discount_rate = ep_tuple[1]
    self.epsilon_greedy = ep_tuple[2]
    self.learning_rate = ep_tuple[3]
    self.policy = ep_tuple[4]
    
  def get_args(self):
    args = ['./carli',
            '--num-steps', str(self.num_steps),
            '--seed', str(self.seed),
            '--environment', self.environment,
            '--discount-rate', str(self.discount_rate),
            '--epsilon-greedy', str(self.epsilon_greedy),
            '--learning-rate', str(self.learning_rate),
            '--policy', self.policy,
            '--output', 'experimental']
    return args
  
  def print_args(self):
    args = self.get_args()
    cmd = ''
    for arg in args:
      cmd += arg + ' '
    cmd += '> ' + self.stdout
    cmd += ' 2> ' + self.stderr
    print cmd
  
  def run(self):
    args = self.get_args()
    f1 = open(self.stdout, 'w')
    f2 = open(self.stderr, 'w')
    subprocess.call(args, stderr=f2, stdout=f1)
    f2.close()
    f1.close()
    return self


dirs = []
experiments = []
for ep_tuple in g_ep_tuples:
  dir = g_dir + '/' + ep_tuple[0]
  dir += '_' + str(ep_tuple[1])
  dir += '_' + str(ep_tuple[2])
  dir += '_' + str(ep_tuple[3])
  dir += '_' + ep_tuple[4]
  if not os.path.isdir(dir):
    os.mkdir(dir)
  dirs.append(dir)
  
  for seed in seeds:
    stderr = dir + '/puddleworld-' + str(seed) + '.err'
    stdout = dir + '/puddleworld-' + str(seed) + '.out'
    experiment = Experiment(args.steps, seed, stderr, stdout, ep_tuple)
    experiments.append(experiment)
    a = experiment.get_args()
    s = a[0]
    for ss in a[1:]:
      s += ' ' + ss
    print s

class Progress:
  def __init__(self, experiments):
    self.lock = thread.allocate_lock()
    
    self.count = {}
    self.finished = {}
    for experiment in experiments:
      try:
        self.count[experiment.ep_tuple] += 1
      except KeyError:
        self.count[experiment.ep_tuple] = 1
      self.finished[experiment.ep_tuple] = 0

  def just_finished(self, experiment):
    self.lock.acquire()
    self.finished[experiment.ep_tuple] += 1
    self.lock.release()

  def all_finished(self, ep_tuple):
    self.lock.acquire()
    num = self.count[ep_tuple]
    fin = self.finished[ep_tuple]
    self.lock.release()
    return fin is num

job_server = pp.Server(args.jobs)
progress = Progress(experiments)
start_time = time.time()
jobs = [(job_server.submit(Experiment.run, (experiment,), (), ('subprocess', 'thread',), callback=progress.just_finished, group=experiment.ep_tuple)) for experiment in experiments]

for ep_tuple, dir in zip(g_ep_tuples, dirs):
  while True:
    job_server.print_stats()
    if progress.all_finished(ep_tuple):
      break
    else:
      time.sleep(5)
  job_server.wait(ep_tuple)
  args = [g_plotter] + glob.glob(dir + '/*.out')
  print 'Plotting data for ' + str(ep_tuple) + '\n'
  subprocess.call(args, stderr=subprocess.PIPE, stdout=subprocess.PIPE)

print 'Total time elapsed: ', time.time() - start_time, 'seconds'