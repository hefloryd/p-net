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

/*
 * Note: this file originally auto-generated by mib2c
 * using mib2c.iterate.conf
 */

#undef LOG_DEBUG
#undef LOG_WARNING
#undef LOG_INFO
#undef LOG_ERROR
#undef LOG_FATAL

#include <net-snmp/agent/snmp_agent.h>
#include <net-snmp/agent/table.h>
#include <net-snmp/library/asn1.h>
#include <net-snmp/library/oid.h>
#include <net-snmp/library/snmp.h>
#include <net-snmp/library/tools.h>
#include <net-snmp/types.h>
#include <net-snmp/varbind_api.h>
#include <stddef.h>
#include <stdint.h>

#include "lldpXdot3LocPortTable.h"
#include "options.h"
#include "osal_log.h"
#include "pf_snmp.h"
#include "pf_types.h"

/** Initializes the lldpXdot3LocPortTable module */
void init_lldpXdot3LocPortTable (pnet_t * pnet)
{
   /* here we initialize all the tables we're planning on supporting */
   initialize_table_lldpXdot3LocPortTable (pnet);
}

static void lldpXdot3LocPortTable_loop_free (
   void * loopctx,
   netsnmp_iterator_info * iinfo)
{
   SNMP_FREE (loopctx);
}

/** Initialize the lldpXdot3LocPortTable table by defining its contents and how
 * it's structured */
void initialize_table_lldpXdot3LocPortTable (pnet_t * pnet)
{
   const oid lldpXdot3LocPortTable_oid[] =
      {1, 0, 8802, 1, 1, 2, 1, 5, 4623, 1, 2, 1};
   const size_t lldpXdot3LocPortTable_oid_len =
      OID_LENGTH (lldpXdot3LocPortTable_oid);
   netsnmp_handler_registration * reg;
   netsnmp_iterator_info * iinfo;
   netsnmp_table_registration_info * table_info;

   reg = netsnmp_create_handler_registration (
      "lldpXdot3LocPortTable",
      lldpXdot3LocPortTable_handler,
      lldpXdot3LocPortTable_oid,
      lldpXdot3LocPortTable_oid_len,
      HANDLER_CAN_RONLY);

   reg->my_reg_void = pnet;

   table_info = SNMP_MALLOC_TYPEDEF (netsnmp_table_registration_info);
   netsnmp_table_helper_add_indexes (
      table_info,
      ASN_INTEGER, /* index: lldpLocPortNum */
      0);
   table_info->min_column = COLUMN_LLDPXDOT3LOCPORTAUTONEGSUPPORTED;
   table_info->max_column = COLUMN_LLDPXDOT3LOCPORTOPERMAUTYPE;

   iinfo = SNMP_MALLOC_TYPEDEF (netsnmp_iterator_info);
   iinfo->get_first_data_point = lldpXdot3LocPortTable_get_first_data_point;
   iinfo->get_next_data_point = lldpXdot3LocPortTable_get_next_data_point;
   iinfo->table_reginfo = table_info;

   iinfo->free_loop_context_at_end = lldpXdot3LocPortTable_loop_free;
   iinfo->myvoid = pnet;

   netsnmp_register_table_iterator (reg, iinfo);
}

netsnmp_variable_list * lldpXdot3LocPortTable_get_first_data_point (
   void ** my_loop_context,
   void ** my_data_context,
   netsnmp_variable_list * put_index_data,
   netsnmp_iterator_info * mydata)
{
   pnet_t * pnet = (pnet_t *)mydata->myvoid;
   pf_port_iterator_t * iterator;

   iterator = SNMP_MALLOC_TYPEDEF (pf_port_iterator_t);
   pf_snmp_init_port_iterator (pnet, iterator);
   *my_loop_context = iterator;

   return lldpXdot3LocPortTable_get_next_data_point (
      my_loop_context,
      my_data_context,
      put_index_data,
      mydata);
}

netsnmp_variable_list * lldpXdot3LocPortTable_get_next_data_point (
   void ** my_loop_context,
   void ** my_data_context,
   netsnmp_variable_list * put_index_data,
   netsnmp_iterator_info * mydata)
{
   netsnmp_variable_list * idx = put_index_data;
   pf_port_iterator_t * iterator;
   int port;

   iterator = (pf_port_iterator_t *)*my_loop_context;
   port = pf_snmp_get_next_port (iterator);
   if (port == 0)
   {
      return NULL;
   }

   snmp_set_var_typed_integer (idx, ASN_INTEGER, port);
   idx = idx->next_variable;

   *my_data_context = (void *)(uintptr_t)port;
   return put_index_data;
}

/** handles requests for the lldpXdot3LocPortTable table */
int lldpXdot3LocPortTable_handler (
   netsnmp_mib_handler * handler,
   netsnmp_handler_registration * reginfo,
   netsnmp_agent_request_info * reqinfo,
   netsnmp_request_info * requests)
{
   netsnmp_request_info * request;
   netsnmp_table_request_info * table_info;
   pnet_t * pnet = reginfo->my_reg_void;
   void * my_data_context;
   pf_snmp_link_status_t link_status;
   int port;

   switch (reqinfo->mode)
   {
      /*
       * Read-support (also covers GetNext requests)
       */
   case MODE_GET:
      for (request = requests; request; request = request->next)
      {
         my_data_context = netsnmp_extract_iterator_context (request);
         table_info = netsnmp_extract_table_info (request);

         LOG_DEBUG (
            PF_SNMP_LOG,
            "lldpXdot3LocPortTable(%d): GET. Column number: %u\n",
            __LINE__,
            table_info->colnum);

         switch (table_info->colnum)
         {
         case COLUMN_LLDPXDOT3LOCPORTAUTONEGSUPPORTED:
            if (my_data_context == NULL)
            {
               netsnmp_set_request_error (reqinfo, request, SNMP_NOSUCHINSTANCE);
               continue;
            }

            port = (int)(uintptr_t)my_data_context;
            pf_snmp_get_link_status (pnet, port, &link_status);
            snmp_set_var_typed_integer (
               request->requestvb,
               ASN_INTEGER,
               link_status.auto_neg_supported);
            break;
         case COLUMN_LLDPXDOT3LOCPORTAUTONEGENABLED:
            if (my_data_context == NULL)
            {
               netsnmp_set_request_error (reqinfo, request, SNMP_NOSUCHINSTANCE);
               continue;
            }

            port = (int)(uintptr_t)my_data_context;
            pf_snmp_get_link_status (pnet, port, &link_status);
            snmp_set_var_typed_integer (
               request->requestvb,
               ASN_INTEGER,
               link_status.auto_neg_enabled);
            break;
         case COLUMN_LLDPXDOT3LOCPORTAUTONEGADVERTISEDCAP:
            if (my_data_context == NULL)
            {
               netsnmp_set_request_error (reqinfo, request, SNMP_NOSUCHINSTANCE);
               continue;
            }

            port = (int)(uintptr_t)my_data_context;
            pf_snmp_get_link_status (pnet, port, &link_status);
            snmp_set_var_typed_value (
               request->requestvb,
               ASN_OCTET_STR,
               &link_status.auto_neg_advertised_cap,
               sizeof (link_status.auto_neg_advertised_cap));
            break;
         case COLUMN_LLDPXDOT3LOCPORTOPERMAUTYPE:
            if (my_data_context == NULL)
            {
               netsnmp_set_request_error (reqinfo, request, SNMP_NOSUCHINSTANCE);
               continue;
            }

            port = (int)(uintptr_t)my_data_context;
            pf_snmp_get_link_status (pnet, port, &link_status);
            snmp_set_var_typed_integer (
               request->requestvb,
               ASN_INTEGER,
               link_status.oper_mau_type);
            break;
         default:
            netsnmp_set_request_error (reqinfo, request, SNMP_NOSUCHOBJECT);
            break;
         }
      }
      break;
   default:
      LOG_DEBUG (
         PF_SNMP_LOG,
         "lldpXdot3LocPortTable(%d): Unknown mode: %u\n",
         __LINE__,
         reqinfo->mode);
      break;
   }
   return SNMP_ERR_NOERROR;
}
