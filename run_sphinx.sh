#!/bin/bash

sudo pocketsphinx_continuous -hmm  /usr/local/share/pocketsphinx/model/en-us/en-us -lm ./word.lm -dict ./word.dic -samprate 16000/8000/48000 -inmic yes