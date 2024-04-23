#include "sensor_collect_task.h"

#include "hal_bsp_ap3216c.h"
#include "hal_bsp_pcf8574.h"
#include "hal_bsp_ssd1306.h"
#include "hal_bsp_ssd1306_bmps.h"

#include "hal_bsp_log.h"
#include "hal_bsp_key.h"
#include "hal_bsp_mqtt.h"

#include "oled_show.h"
#include "sys_config.h"


msg_data_t sys_msg_data = {0};    // 传感器的数据

margin_t   png_left       = { .top = 16, .left = 10, };// 左侧图片  
margin_t   png_right      = { .top = 16, .left = 68, };// 右侧图片  

margin_t   text_left      = { .top = 3, .left = 18, };// 左侧图片名称 
margin_t   text_right     = { .top = 3, .left = 76, };// 右侧图片名称


/**
 * @brief  显示湿度页面
 * @note   
 * @param  val: 
 * @retval None
 */
void show_page()
{
  SSD1306_ShowStr(0, 0, " Smart Security", 16);

  if(sys_msg_data.buzzerStatus != 0){  
    // 蜂鸣器状态 开启
    SSD1306_DrawBMP(png_right.left, png_right.top, 32, 32, bmp_32X32_BaoJing);   // 显示 报警
    SSD1306_ShowStr(text_right.left, text_right.top, "Yes", 16);
  }
  else{
    // 关闭 
    SSD1306_DrawBMP(png_right.left, png_right.top, 32, 32, bmp_32X32_No_BaoJing);   // 显示 不报警状态
    SSD1306_ShowStr(text_right.left, text_right.top, "No ", 16);
  }

  if(sys_msg_data.is_Body != 0){
    SSD1306_DrawBMP(png_left.left, png_left.top, 32, 32, bmp_32X32_Body);   // 显示 有人
    SSD1306_ShowStr(text_left.left, text_left.top, "Yes", 16);
  }
  else{
    SSD1306_DrawBMP(png_left.left, png_left.top, 32, 32, bmp_32X32_No_Body);   // 显示 无人
    SSD1306_ShowStr(text_left.left, text_left.top, "No ", 16);
  }
}

/**
 * @brief  传感器采集任务
 * @note   
 * @retval None
 */
void sensor_collect_task(void)
{
  while(1)
  {
    // 采集传感器的值
    uint16_t irData, alsData;
    AP3216C_ReadData(&irData, &alsData, &sys_msg_data.psData);
    // 逻辑判断 当接近传感器检测有物体接近的时候，表示有人靠近
    
    printf("psData: %d\n", sys_msg_data.psData);

    sys_msg_data.is_Body = (sys_msg_data.psData >= 500 ? 1 : 0);
    // 显示在OLED显示屏上
    show_page();

    // 是否开启自动控制
    if(sys_msg_data.nvFlash.smartControl_flag != 0)  
    {
      if(sys_msg_data.is_Body != 0)
      {
        // 开启蜂鸣器报警
        sys_msg_data.buzzerStatus = 1;
        sys_msg_data.pcf8574_io.bit.p1 ^= 0x01;
      }
      else{
        // 关闭蜂鸣器报警
        sys_msg_data.buzzerStatus = 0;
        sys_msg_data.pcf8574_io.bit.p1 = 1;
      }
    }
    else{
      if(sys_msg_data.buzzerStatus != 0)
        sys_msg_data.pcf8574_io.bit.p1 ^= 0x01; // 开启蜂鸣器报警
      else
        sys_msg_data.pcf8574_io.bit.p1 = 1; // 关闭蜂鸣器报警
    }

    PCF8574_Write(sys_msg_data.pcf8574_io.all);
    usleep(100*1000);
  }
}




