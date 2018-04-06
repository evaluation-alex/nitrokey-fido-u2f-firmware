#!/bin/bash

virtualenv env2 -p `which python2`
. ./env2/bin/activate
pip install -r requirements.txt

echo "Run . ./env2/bin/activate"

