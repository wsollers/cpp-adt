#!/bin/sh

#Upgrade pip
python3 -m pip install --upgrade pip

#install checkov
pip3 install checkov

#Upgrade checkov
pip3 install -U checkov

#Run checkov
checkov -d .
