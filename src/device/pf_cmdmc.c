/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2018 rt-labs AB, Sweden.
 *
 * This software is dual-licensed under GPLv3 and a commercial
 * license. See the file LICENSE.md distributed with this software for
 * full license information.
 ********************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "pf_cmdmc.h"
#include "pf_types.h"

int pf_cmdmc_activate_req (pf_ar_t * p_ar)
{
   return 0;
}

int pf_cmdmc_close_req (pf_ar_t * p_ar)
{
   return 0;
}

int pf_cmdmc_cpm_state_ind (pf_ar_t * p_ar, uint16_t ix, bool start)
{
   return 0;
}
