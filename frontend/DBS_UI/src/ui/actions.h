#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_switch_to_fingerprint(lv_event_t * e);
extern void action_switch_to_main(lv_event_t * e);
extern void action_print_receipt(lv_event_t * e);
extern void action_switch_to_money_transfer(lv_event_t * e);
extern void action_switch_to_cash_deposit(lv_event_t * e);
extern void action_switch_to_transac_his(lv_event_t * e);
extern void action_switch_to_dashboard(lv_event_t * e);
extern void action_switch_to_account_num(lv_event_t * e);
extern void action_switch_to_amount(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/