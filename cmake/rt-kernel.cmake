#********************************************************************
#        _       _         _
#  _ __ | |_  _ | |  __ _ | |__   ___
# | '__|| __|(_)| | / _` || '_ \ / __|
# | |   | |_  _ | || (_| || |_) |\__ \
# |_|    \__|(_)|_| \__,_||_.__/ |___/
#
# www.rt-labs.com
# Copyright 2018 rt-labs AB, Sweden.
#
# This software is dual-licensed under GPLv3 and a commercial
# license. See the file LICENSE.md distributed with this software for
# full license information.
#*******************************************************************/

target_sources(pn_dev PRIVATE
  sample_app/main_rtk.c
  )

target_sources(pf_test PRIVATE
  ${OSAL_DIR}/fixup/stubs.c
  )

target_compile_options(profinet
  PRIVATE
  -Wall
  -Wextra
  -Werror
  -Wno-unused-parameter
  )

# Workaround duplicate definition of assert by including osal
# definition before anything else.
include_directories(BEFORE
  ${OSAL_DIR}/fixup
  )
