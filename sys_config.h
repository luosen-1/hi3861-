#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H

#include "cmsis_os2.h"
#include "hal_bsp_structAll.h"

// DeviceSecret fs12345678
// 设备ID
#define DEVICE_ID                           "6260b1ac8778ce13ebc351cb_hi3861_security"
// MQTT客户端ID
#define MQTT_CLIENT_ID                      "6260b1ac8778ce13ebc351cb_hi3861_security_0_0_2022042101"
// MQTT用户名
#define MQTT_USER_NAME                      "6260b1ac8778ce13ebc351cb_hi3861_security"
// MQTT密码
#define MQTT_PASS_WORD                      "27032efb5ca0fe775d5b1aa29b3de2fa14f10bce4feb5987628b265a654cd3f9"
// 华为云平台的IP地址
#define SERVER_IP_ADDR                      "121.36.42.100"   
// 华为云平台的IP端口号
#define SERVER_IP_PORT                      1883  
// 订阅 接收控制命令的主题
#define MQTT_TOPIC_SUB_COMMANDS             "$oc/devices/%s/sys/commands/#" 
// 发布 成功接收到控制命令后的主题
#define MQTT_TOPIC_PUB_COMMANDS_REQ         "$oc/devices/%s/sys/commands/response/request_id=%s"  
#define MALLOC_MQTT_TOPIC_PUB_COMMANDS_REQ  "$oc/devices//sys/commands/response/request_id="  
// 发布 设备属性数据的主题
#define MQTT_TOPIC_PUB_PROPERTIES           "$oc/devices/%s/sys/properties/report"        
#define MALLOC_MQTT_TOPIC_PUB_PROPERTIES    "$oc/devices//sys/properties/report"        
#define MQTT_PAYLOAD_PUB                    "{\"services\":[{\"service_id\":\"base\",\"properties\":{\"isBody\":\"%s\",\"autoMode\":\"%s\",\"buzzer\":\"%s\"}}]}"

typedef struct
{
  int top;  // 上边距
  int left; // 下边距
} margin_t;     // 边距类型

typedef struct message_data
{
  unsigned char buzzerStatus;      // 风扇的状态
  unsigned char is_Body;      // 有人或没人
  unsigned short psData;   // 接近传感器值
  hi_nv_save_sensor_threshold nvFlash;
  tn_pcf8574_io_t pcf8574_io;
}msg_data_t;

#endif

