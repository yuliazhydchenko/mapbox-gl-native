#!/usr/bin/env bash

function mapbox_time_start {
    :
}

function mapbox_time_finish {
    :
}

function mapbox_time {
    :
}

function mapbox_fold {
    :
}

function mapbox_nanoseconds {
    :
}

export JOBS=${CIRCLE_NODE_TOTAL:-6}
export -f mapbox_fold
export -f mapbox_nanoseconds
export -f mapbox_time
export -f mapbox_time_start
export -f mapbox_time_finish
