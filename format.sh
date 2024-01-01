#!/bin/bash

cd $(dirname ${BASH_SOURCE})

find -iname '*.hh' -or -iname '*.cc' | xargs clang-format -i
