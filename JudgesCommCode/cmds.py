"""
  @file   roboboat/cmds.py
  @author Brian Kim
  @author Adam DeAngelo
  @brief  a set of functions to make http requests 
          for the roboboat challenge
"""

import json
import urllib, urllib2

base_url = 'http://ec2-52-7-253-202.compute-1.amazonaws.com'
course = '/courseA'
teamid = '/VU'

a = '/run/start'
z = '/run/end'
obs = '/obstacleAvoidance'
ad  = '/automatedDocking'
p = '/pinger'
imd = '/interop/images'
imu = '/interop/report'


def start_cmd_create():
  return base_url+a+course+teamid

def start_cmd_request():
  return urllib2.urlopen(init_cmd_create(),'')

def start():
  return json.loads(init_cmd_request().read())
  
def obs_cmd_create():
  return base_url+obs+course+teamid

def obs_cmd_request():
  return urllib2.urlopen(obs_cmd_create())
  
def obs_cmd_getCode():
  return json.loads(obs_cmd_request().read())

def autodock_cmd_create():
  return base_url+ad+course+teamid

def autodock_cmd_request():
  return urllib2.urlopen(autodock_cmd_create)

def autodock_cmd_getCode():
  return json.loads(autodock_cmd_request().read())

def ping_cmd_create():
  return base_url+p+course+teamid

def ping_cmd_request():
  return urllib2.urlopen(ping_cmd_create(),'buoy color')

def pinger():
  return json.loads(ping_cmd_request().read())

def imgdwnld_cmd_create():
  return base_url+imd+course+teamid

def imgdwnld_cmd_request():
  return urllib2.urlopen(imgdwnld_cmd_create)

def imgdwnld():
  return json.loads(imgdwnld_cmd_request().read())

def imgupld_cmd_create():
  return base_url+imu+course+teamid

def imgupld_cmd_request():
  return urllib2.urlopen(imgupld_cmd_create(),'the image that we decipher')

def imgupld():
  return json.loads(imgupld_cmd_request().read())

def end_cmd_create():
  return base_url+z+course+teamid

def end_cmd_request():
  return urllib2.urlopen(end_cmd_create(),'')

def end():
  return json.loads(end_cmd_request().read())


