#!/bin/bash

read -p "Delete frames? [Y/N]" yn
case "$yn" in 
  [yY]) rm frames/*.* ;; 
esac
