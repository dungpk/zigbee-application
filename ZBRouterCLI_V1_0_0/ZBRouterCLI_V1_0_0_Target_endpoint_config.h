// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef SILABS_AF_ENDPOINT_CONFIG
#define SILABS_AF_ENDPOINT_CONFIG


// Fixed number of defined endpoints
#define FIXED_ENDPOINT_COUNT (1)




// Generated attributes
#define GENERATED_ATTRIBUTES { \
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0001 } }, /* 0 / Basic / cluster revision*/\
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x03 } }, /* 1 / Basic / ZCL version*/\
    { 0x0001, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 2 / Basic / application version*/\
    { 0x0002, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 3 / Basic / stack version*/\
    { 0x0003, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 4 / Basic / hardware version*/\
    { 0x0004, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 5 / Basic / manufacturer name*/\
    { 0x0005, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 6 / Basic / model identifier*/\
    { 0x0006, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 7 / Basic / date code*/\
    { 0x0007, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 8 / Basic / power source*/\
    { 0x0008, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0xFF } }, /* 9 / Basic / generic device class*/\
    { 0x0009, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0xFF } }, /* 10 / Basic / generic device type*/\
    { 0x000A, ZCL_OCTET_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 11 / Basic / product code*/\
    { 0x000B, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 65, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 12 / Basic / product url*/\
    { 0x4000, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, /* 13 / Basic / sw build id*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0001 } }, /* 14 / Basic / cluster revision*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT), { (uint8_t*)0x0001 } }, /* 15 / Identify / cluster revision*/\
    { 0x0000, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 16 / Identify / identify time*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 17 / Identify / cluster revision*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT), { (uint8_t*)0x0001 } }, /* 18 / Groups / cluster revision*/\
    { 0x0000, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 19 / Groups / name support*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 20 / Groups / cluster revision*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT), { (uint8_t*)0x0001 } }, /* 21 / Scenes / cluster revision*/\
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 22 / Scenes / scene count*/\
    { 0x0001, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 23 / Scenes / current scene*/\
    { 0x0002, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0000 } }, /* 24 / Scenes / current group*/\
    { 0x0003, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 25 / Scenes / scene valid*/\
    { 0x0004, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 26 / Scenes / name support*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 27 / Scenes / cluster revision*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT), { (uint8_t*)0x0001 } }, /* 28 / On/off / cluster revision*/\
    { 0x0000, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }, /* 29 / On/off / on/off*/\
    { 0x4000, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x01 } }, /* 30 / On/off / global scene control*/\
    { 0x4001, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 31 / On/off / on time*/\
    { 0x4002, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 32 / On/off / off wait time*/\
    { 0x4003, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0xFF } }, /* 33 / On/off / start up on off*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 34 / On/off / cluster revision*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT), { (uint8_t*)0x0001 } }, /* 35 / Level Control / cluster revision*/\
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }, /* 36 / Level Control / current level*/\
    { 0x0001, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0000 } }, /* 37 / Level Control / remaining time*/\
    { 0x000F, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x00 } }, /* 38 / Level Control / options*/\
    { 0x4000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x33 } }, /* 39 / Level Control / start up current level*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 40 / Level Control / cluster revision*/\
  }


// Cluster function static arrays
#define GENERATED_FUNCTION_ARRAYS \
const EmberAfGenericClusterFunction emberAfFuncArrayIdentifyClusterServer[] = { (EmberAfGenericClusterFunction)emberAfIdentifyClusterServerInitCallback,(EmberAfGenericClusterFunction)emberAfIdentifyClusterServerAttributeChangedCallback}; \
const EmberAfGenericClusterFunction emberAfFuncArrayGroupsClusterServer[] = { (EmberAfGenericClusterFunction)emberAfGroupsClusterServerInitCallback}; \
const EmberAfGenericClusterFunction emberAfFuncArrayScenesClusterServer[] = { (EmberAfGenericClusterFunction)emberAfScenesClusterServerInitCallback}; \
const EmberAfGenericClusterFunction emberAfFuncArrayOnOffClusterServer[] = { (EmberAfGenericClusterFunction)emberAfOnOffClusterServerInitCallback,(EmberAfGenericClusterFunction)emberAfOnOffClusterServerAttributeChangedCallback}; \
const EmberAfGenericClusterFunction emberAfFuncArrayLevelControlClusterServer[] = { (EmberAfGenericClusterFunction)emberAfLevelControlClusterServerInitCallback}; \


// Clusters definitions
#define GENERATED_CLUSTERS { \
    { 0x0000, (EmberAfAttributeMetadata*)&(generatedAttributes[0]), 1, 0, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0000, (EmberAfAttributeMetadata*)&(generatedAttributes[1]), 14, 0, (CLUSTER_MASK_SERVER), NULL,  },    \
    { 0x0003, (EmberAfAttributeMetadata*)&(generatedAttributes[15]), 1, 2, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0003, (EmberAfAttributeMetadata*)&(generatedAttributes[16]), 2, 4, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION| CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION), emberAfFuncArrayIdentifyClusterServer, },    \
    { 0x0004, (EmberAfAttributeMetadata*)&(generatedAttributes[18]), 1, 2, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0004, (EmberAfAttributeMetadata*)&(generatedAttributes[19]), 2, 3, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION), emberAfFuncArrayGroupsClusterServer, },    \
    { 0x0005, (EmberAfAttributeMetadata*)&(generatedAttributes[21]), 1, 2, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0005, (EmberAfAttributeMetadata*)&(generatedAttributes[22]), 6, 8, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION), emberAfFuncArrayScenesClusterServer, },    \
    { 0x0006, (EmberAfAttributeMetadata*)&(generatedAttributes[28]), 1, 2, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0006, (EmberAfAttributeMetadata*)&(generatedAttributes[29]), 6, 9, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION| CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION), emberAfFuncArrayOnOffClusterServer, },    \
    { 0x0008, (EmberAfAttributeMetadata*)&(generatedAttributes[35]), 1, 2, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0008, (EmberAfAttributeMetadata*)&(generatedAttributes[36]), 5, 7, (CLUSTER_MASK_SERVER| CLUSTER_MASK_INIT_FUNCTION), emberAfFuncArrayLevelControlClusterServer, },    \
  }


// Endpoint types
#define GENERATED_ENDPOINT_TYPES {        \
    { (EmberAfCluster*)&(generatedClusters[0]), 12, 41 }, \
  }


// Cluster manufacturer codes
#define GENERATED_CLUSTER_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT (0)

// Attribute manufacturer codes
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT (0)


// Largest attribute size is needed for various buffers
#define ATTRIBUTE_LARGEST (65)
// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (193)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE 41

// Array of endpoints that are supported
#define FIXED_ENDPOINT_ARRAY { 1 }

// Array of profile ids
#define FIXED_PROFILE_IDS { 260 }

// Array of device ids
#define FIXED_DEVICE_IDS { 256 }

// Array of device versions
#define FIXED_DEVICE_VERSIONS { 1 }

// Array of endpoint types supported on each endpoint
#define FIXED_ENDPOINT_TYPES { 0 }

// Array of networks supported on each endpoint
#define FIXED_NETWORKS { 0 }


#define EMBER_AF_GENERATED_PLUGIN_INIT_FUNCTION_DECLARATIONS \
  void emberAfPluginReportingInitCallback(void); \
  void emberAfPluginInterpanInitCallback(void); \
  void emberAfPluginCountersInitCallback(void); \


#define EMBER_AF_GENERATED_PLUGIN_INIT_FUNCTION_CALLS \
  emberAfPluginReportingInitCallback(); \
  emberAfPluginInterpanInitCallback(); \
  emberAfPluginCountersInitCallback(); \


#define EMBER_AF_GENERATED_PLUGIN_NCP_INIT_FUNCTION_DECLARATIONS \
  void emberAfPluginInterpanNcpInitCallback(bool memoryAllocation); \


#define EMBER_AF_GENERATED_PLUGIN_NCP_INIT_FUNCTION_CALLS \
  emberAfPluginInterpanNcpInitCallback(memoryAllocation); \


#define EMBER_AF_GENERATED_PLUGIN_STACK_STATUS_FUNCTION_DECLARATIONS \
  void emberAfPluginReportingStackStatusCallback(EmberStatus status); \
  void emberAfPluginNetworkSteeringStackStatusCallback(EmberStatus status); \


#define EMBER_AF_GENERATED_PLUGIN_STACK_STATUS_FUNCTION_CALLS \
  emberAfPluginReportingStackStatusCallback(status); \
  emberAfPluginNetworkSteeringStackStatusCallback(status); \


// Generated data for the command discovery
#define GENERATED_COMMANDS { \
    { 0x0000, 0x00, COMMAND_MASK_INCOMING_SERVER }, /* Basic / ResetToFactoryDefaults */ \
    { 0x0003, 0x00, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Identify / Identify */ \
    { 0x0003, 0x00, COMMAND_MASK_OUTGOING_SERVER }, /* Identify / IdentifyQueryResponse */ \
    { 0x0003, 0x01, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Identify / IdentifyQuery */ \
    { 0x0004, 0x00, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Groups / AddGroup */ \
    { 0x0004, 0x00, COMMAND_MASK_OUTGOING_SERVER }, /* Groups / AddGroupResponse */ \
    { 0x0004, 0x01, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Groups / ViewGroup */ \
    { 0x0004, 0x01, COMMAND_MASK_OUTGOING_SERVER }, /* Groups / ViewGroupResponse */ \
    { 0x0004, 0x02, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Groups / GetGroupMembership */ \
    { 0x0004, 0x02, COMMAND_MASK_OUTGOING_SERVER }, /* Groups / GetGroupMembershipResponse */ \
    { 0x0004, 0x03, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Groups / RemoveGroup */ \
    { 0x0004, 0x03, COMMAND_MASK_OUTGOING_SERVER }, /* Groups / RemoveGroupResponse */ \
    { 0x0004, 0x04, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Groups / RemoveAllGroups */ \
    { 0x0004, 0x05, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Groups / AddGroupIfIdentifying */ \
    { 0x0005, 0x00, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / AddScene */ \
    { 0x0005, 0x00, COMMAND_MASK_OUTGOING_SERVER }, /* Scenes / AddSceneResponse */ \
    { 0x0005, 0x01, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / ViewScene */ \
    { 0x0005, 0x01, COMMAND_MASK_OUTGOING_SERVER }, /* Scenes / ViewSceneResponse */ \
    { 0x0005, 0x02, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / RemoveScene */ \
    { 0x0005, 0x02, COMMAND_MASK_OUTGOING_SERVER }, /* Scenes / RemoveSceneResponse */ \
    { 0x0005, 0x03, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / RemoveAllScenes */ \
    { 0x0005, 0x03, COMMAND_MASK_OUTGOING_SERVER }, /* Scenes / RemoveAllScenesResponse */ \
    { 0x0005, 0x04, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / StoreScene */ \
    { 0x0005, 0x04, COMMAND_MASK_OUTGOING_SERVER }, /* Scenes / StoreSceneResponse */ \
    { 0x0005, 0x05, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / RecallScene */ \
    { 0x0005, 0x06, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Scenes / GetSceneMembership */ \
    { 0x0005, 0x06, COMMAND_MASK_OUTGOING_SERVER }, /* Scenes / GetSceneMembershipResponse */ \
    { 0x0006, 0x00, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* On/off / Off */ \
    { 0x0006, 0x01, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* On/off / On */ \
    { 0x0006, 0x02, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* On/off / Toggle */ \
    { 0x0008, 0x00, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / MoveToLevel */ \
    { 0x0008, 0x01, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / Move */ \
    { 0x0008, 0x02, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / Step */ \
    { 0x0008, 0x03, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / Stop */ \
    { 0x0008, 0x04, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / MoveToLevelWithOnOff */ \
    { 0x0008, 0x05, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / MoveWithOnOff */ \
    { 0x0008, 0x06, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / StepWithOnOff */ \
    { 0x0008, 0x07, COMMAND_MASK_OUTGOING_CLIENT | COMMAND_MASK_INCOMING_SERVER }, /* Level Control / StopWithOnOff */ \
  }
#define EMBER_AF_GENERATED_COMMAND_COUNT (38)

// Command manufacturer codes
#define GENERATED_COMMAND_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_COMMAND_MANUFACTURER_CODE_COUNT (0)


// Generated reporting configuration defaults
#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS {\
  { EMBER_ZCL_REPORTING_DIRECTION_REPORTED, 1, 0x0006, 0x0000, CLUSTER_MASK_SERVER, 0x0000, 1, 65534, 0 }, \
  { EMBER_ZCL_REPORTING_DIRECTION_REPORTED, 1, 0x0008, 0x0000, CLUSTER_MASK_SERVER, 0x0000, 10, 60, 1 }, \
}
#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS_TABLE_SIZE (2)
#endif // SILABS_AF_ENDPOINT_CONFIG
