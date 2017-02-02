#!/usr/bin/env python

from rospy import init_node, is_shutdown


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


if __name__ == '__main__':

  init_node('input_test')
  
  getch = _GetchUnix()

  while not is_shutdown():

      print "gimme something, please?"
      #something = raw_input()
      something = getch() 
      print "thanks for giving me " + something
