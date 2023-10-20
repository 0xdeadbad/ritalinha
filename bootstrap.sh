#!/usr/bin/env bash
shopt -s extglob

TMP_DIR=template/tmp
([[ ! -d "${TMP_DIR}" ]] && mkdir -p ${TMP_DIR}) || rm -f ${TMP_DIR}/*
rm -f src/*/config.mk src/*/Makefile src/common.mk common.mk config.mk Makefile

for dir in ./src/*/; do
    export module=$(basename $dir)
    export MODULE=${module^^}
    export C_FILES=("$dir"*.c)
    _OBJS=()
    _DEPS=()

    for i in "${C_FILES[@]//.c/.o}"; do
        _OBJS+=("$(basename $i)")
    done

    for i in "${C_FILES[@]//.c/.h}"; do
        _DEPS+=("${module}/$(basename $i)")
    done

    export OBJS="${_OBJS[@]}"
    export DEPS="${_DEPS[@]}"

    touch ${TMP_DIR}/objects_targets
    touch ${TMP_DIR}/modules_dirs
    touch ${TMP_DIR}/modules_incs
    touch ${TMP_DIR}/modules_deps
    touch ${TMP_DIR}/obj_patsubst

    envsubst '${MODULE}' < template/src/Makefile.tpl > ${dir}/Makefile
    envsubst < template/src/config.mk.tpl > ${dir}/config.mk
    envsubst '${MODULE}' < template/objects_targets.tpl >> ${TMP_DIR}/objects_targets
    envsubst '${MODULE}' < template/obj_patsubst.tpl >> ${TMP_DIR}/obj_patsubst
    envsubst '${MODULE} ${module}' < template/modules_dirs.tpl >> ${TMP_DIR}/modules_dirs
    envsubst '${MODULE} ${module}' < template/modules_incs.tpl >> ${TMP_DIR}/modules_incs
    envsubst '${MODULE} ${module}' < template/modules_deps.tpl >> ${TMP_DIR}/modules_deps
done

export MODULES_DIRS="$(cat ${TMP_DIR}/modules_dirs)"
export MODULES_INCS="$(cat ${TMP_DIR}/modules_incs)"
export MODULES_DEPS="$(cat ${TMP_DIR}/modules_deps)"
export OBJ_PATSUBST="$(cat ${TMP_DIR}/obj_patsubst)"
export MODULES_TARGETS=$(cat ${TMP_DIR}/objects_targets)

envsubst '${MODULES_DIRS} ${MODULES_INCS} ${MODULES_DEPS}' < template/common.mk.tpl > common.mk
envsubst '${OBJ_PATSUBST} ${MODULES_TARGETS}' < template/Makefile.tpl > Makefile
cat template/src/common.mk.tpl > src/common.mk
cat template/config.mk.tpl > config.mk

command -v bear &> /dev/null && bear -- make > /dev/null 
make clean > /dev/null
rm -f ${TMP_DIR}/* && rmdir ${TMP_DIR}