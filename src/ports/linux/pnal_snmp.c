/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2020 rt-labs AB, Sweden.
 *
 * This software is dual-licensed under GPLv3 and a commercial
 * license. See the file LICENSE.md distributed with this software for
 * full license information.
 ********************************************************************/

#include <net-snmp/agent/snmp_agent.h>
#include <net-snmp/agent/snmp_vars.h>
#include <net-snmp/library/snmp_api.h>
#include <net-snmp/library/snmp_debug.h>

#include "pnal.h"
#include "pnal_options.h"
#include "osal.h"
#include "mib/lldpConfigManAddrTable.h"
#include "mib/lldpLocalSystemData.h"
#include "mib/lldpLocManAddrTable.h"
#include "mib/lldpLocPortTable.h"
#include "mib/lldpRemManAddrTable.h"
#include "mib/lldpRemTable.h"
#include "mib/lldpXdot3LocPortTable.h"
#include "mib/lldpXdot3RemPortTable.h"
#include "mib/lldpXPnoLocTable.h"
#include "mib/lldpXPnoRemTable.h"
#include "mib/system_mib.h"

struct pnet;

static void pnal_snmp_thread (void * arg)
{
   struct pnet * pnet = arg;

   snmp_disable_log();

   /* make us an agentx client. */
   netsnmp_enable_subagent();

   /* initialize the agent library */
   init_agent ("lldpMIB");

   /* init mib code */
   init_system_mib (pnet);
   init_lldpLocalSystemData (pnet);
   init_lldpLocPortTable (pnet);
   init_lldpConfigManAddrTable (pnet);
   init_lldpLocManAddrTable (pnet);
   init_lldpRemManAddrTable (pnet);
   init_lldpRemTable (pnet);
   init_lldpXdot3LocPortTable (pnet);
   init_lldpXdot3RemPortTable (pnet);
   init_lldpXPnoLocTable (pnet);
   init_lldpXPnoRemTable (pnet);

   /* read lldpMIB.conf files. */
   init_snmp ("lldpMIB");

   for (;;)
   {
      agent_check_and_process (1); /* 0 == don't block */
   }
}

int pnal_snmp_init (struct pnet * pnet)
{
   os_thread_create (
      "pn_snmp",
      PNET_SNMP_PRIO,
      PNET_SNMP_STACK_SIZE,
      pnal_snmp_thread,
      pnet);
   return 0;
}
