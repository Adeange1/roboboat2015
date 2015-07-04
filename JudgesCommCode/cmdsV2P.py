"""
  @file   roboboat/cmds.py
  @author Brian Kim
  @2ndauthor Adam DeAngelo
  @brief  a set of functions to make http requests 
          for the roboboat challenge
"""

import json
import urllib, urllib2

base_url = 'http://ec2-52-7-253-202.compute-1.amazonaws.com'
personalserver = 'http://192.168.7.3'
course = '/courseA'
teamid = '/VU'

a = '/run/start'
z = '/run/end'
obs = '/obstacleAvoidance'
ad  = '/automatedDocking'
p = '/pinger'
imd = '/interop/images'
imu = '/interop/report'


def init_cmd_create():
  return personalserver+a+course+teamid

def init_cmd_request():
  return urllib2.urlopen(init_cmd_create(),'')

def init():
  return json.loads(init_cmd_request().read())
  
def obs_cmd_create():
  return personalserver+obs+course+teamid

def obs_cmd_request():
  return urllib2.urlopen(obs_cmd_create())
  
def obs_cmd_getCode():
  return json.loads(obs_cmd_request().read())

def autodock_cmd_create():
  return personalserver+ad+course+teamid

def autodock_cmd_request():
  return urllib2.urlopen(autodock_cmd_create)

def autodock_cmd_getCode():
  return json.loads(autodock_cmd_request().read())

def ping_cmd_create():
  return personalserver+p+course+teamid

def ping_cmd_request():
  return urllib2.urlopen(ping_cmd_create(),'buoy color')

def pinger():
  return json.loads(ping_cmd_request().read())

def imgdwnld_cmd_create():
  return personalserver+imd+course+teamid

def imgdwnld_cmd_request():
  return urllib2.urlopen(imgdwnld_cmd_create)

def imgdwnld():
  return json.loads(imgdwnld_cmd_request().read())

def imgupld_cmd_create():
  return personalserver+imu+course+teamid

def imgupld_cmd_request():
  return urllib2.urlopen(imgupld_cmd_create(),'the image that we decipher')

def imgupld():
  return json.loads(imgupld_cmd_request().read())

def end_cmd_create():
  return personalserver+z+course+teamid

def end_cmd_request():
  return urllib2.urlopen(end_cmd_create(),'')

def end():
  return json.loads(end_cmd_request().read())


