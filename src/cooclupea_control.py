#!/usr/bin/python

import subprocess
import sys




def show_info()
   p = subprocess.Popen("pgrep cooclupea", stdout=subprocess.PIPE, shell=True)

   (output, err) = p.communicate()

   p_status = p.wait()

   //print output

   p = subprocess.Popen("kill -31 "+output, stdout=subprocess.PIPE, shell=True)

   (output, err) = p.communicate()

   p_status = p.wait()

def start()
   p = subprocess.Popen("./cooclupea -c pandora.config", stdout=subprocess.PIPE, shell=True)

   (output, err) = p.communicate()

   //p_status = p.wait()


	
