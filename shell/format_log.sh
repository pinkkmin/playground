#!/bin/bash
#
# learn-shell: print log. 

trace() {
    echo "$(date +'%Y-%m-%d %H:%M:%S') \033[36mTRACE\033[0m $@" >&2
}

info() {
    echo "$(date +'%Y-%m-%d %H:%M:%S') \033[32mINFO\033[0m  $@" >&2
}

debug() {
    echo "$(date +'%Y-%m-%d %H:%M:%S') \033[34mDEBUG\033[0m $@" >&2
}

warn(){
    echo $(date +'%Y-%m-%d %H:%M:%S') "\033[33mWARN\033[0m  $@" >&2
}

err() {
    echo "$(date +'%Y-%m-%d %H:%M:%S') \033[31mERROR\033[0m $@" >&2
}

trace "print warn message."
debug "print debug message."
info "print info message."
warn "print warn message."
err "print error message."
