#!/usr/bin/env bash

function getDir(){
    # return the directory containing this script
    local SOURCE="${BASH_SOURCE[0]}"
    local DIR=""
    while [ -h "${SOURCE}" ]; do
      DIR="$(cd -P "$(dirname "${SOURCE}")" && pwd)"
      SOURCE="$(readlink "${SOURCE}")"
      [[ ${SOURCE} != /* ]] && SOURCE="${DIR}/$SOURCE"
    done
    DIR="$(cd -P "$(dirname "${SOURCE}")" && pwd)"
    echo ${DIR}
}

DIR=$(getDir)
cd ${DIR} && git submodule update --init && git submodule sync
