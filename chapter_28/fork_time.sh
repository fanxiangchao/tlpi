#!/bin/bash

echo "====== Compare fork and vfork ======"
echo "fork time:"
time ./fork_time fork
echo "vfork time:"
time ./fork_time vfork