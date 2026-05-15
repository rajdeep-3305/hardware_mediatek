/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MTK_DRIVER_NL80211_H_
#define _MTK_DRIVER_NL80211_H_

#include <linux/wireless.h>

#ifndef BITS
/* bits range: for example BITS(16,23) = 0xFF0000
 *   ==>  (BIT(m)-1)   = 0x0000FFFF     ~(BIT(m)-1)   => 0xFFFF0000
 *   ==>  (BIT(n+1)-1) = 0x00FFFFFF
 */
#define BITS(m, n) (~(BIT(m) - 1) & ((BIT(n) - 1) | BIT(n)))
#endif /* BIT */

#define OUI_MTK 0x000CE7

extern void nl80211_vendor_event_mtk(struct wpa_driver_nl80211_data*, u32, u8*, size_t);

enum nl80211_testmode_sta_link_statistics_attr {
    __NL80211_TESTMODE_STA_STATISTICS_INVALID = 0,
    NL80211_TESTMODE_STA_STATISTICS_VERSION,
    NL80211_TESTMODE_STA_STATISTICS_MAC,
    NL80211_TESTMODE_STA_STATISTICS_LINK_SCORE,
    NL80211_TESTMODE_STA_STATISTICS_FLAG,

    NL80211_TESTMODE_STA_STATISTICS_PER,
    NL80211_TESTMODE_STA_STATISTICS_RSSI,
    NL80211_TESTMODE_STA_STATISTICS_PHY_MODE,
    NL80211_TESTMODE_STA_STATISTICS_TX_RATE,

    NL80211_TESTMODE_STA_STATISTICS_TOTAL_CNT,
    NL80211_TESTMODE_STA_STATISTICS_THRESHOLD_CNT,

    NL80211_TESTMODE_STA_STATISTICS_AVG_PROCESS_TIME,
    NL80211_TESTMODE_STA_STATISTICS_MAX_PROCESS_TIME,
    NL80211_TESTMODE_STA_STATISTICS_AVG_HIF_PROCESS_TIME,
    NL80211_TESTMODE_STA_STATISTICS_MAX_HIF_PROCESS_TIME,

    NL80211_TESTMODE_STA_STATISTICS_FAIL_CNT,
    NL80211_TESTMODE_STA_STATISTICS_TIMEOUT_CNT,
    NL80211_TESTMODE_STA_STATISTICS_AVG_AIR_TIME,

    NL80211_TESTMODE_STA_STATISTICS_TC_EMPTY_CNT_ARRAY,
    NL80211_TESTMODE_STA_STATISTICS_TC_QUE_LEN_ARRAY,

    NL80211_TESTMODE_STA_STATISTICS_TC_AVG_QUE_LEN_ARRAY,
    NL80211_TESTMODE_STA_STATISTICS_TC_CUR_QUE_LEN_ARRAY,

    /*
     * how many packages TX during statistics interval
     */
    NL80211_TESTMODE_STA_STATISTICS_ENQUEUE,

    /*
     * how many packages TX during statistics interval
     */
    NL80211_TESTMODE_STA_STATISTICS_STA_ENQUEUE,

    /*
     * how many packages dequeue during statistics interval
     */
    NL80211_TESTMODE_STA_STATISTICS_DEQUEUE,

    /*
     * how many packages dequeue during statistics interval
     */
    NL80211_TESTMODE_STA_STATISTICS_STA_DEQUEUE,

    /*
     * how many TC[0-3] resource back from firmware during
     * statistics interval
     */
    NL80211_TESTMODE_STA_STATISTICS_RB_ARRAY,
    NL80211_TESTMODE_STA_STATISTICS_NO_TC_ARRAY,
    NL80211_TESTMODE_STA_STATISTICS_TC_USED_ARRAY,
    NL80211_TESTMODE_STA_STATISTICS_TC_WANTED_ARRAY,

    NL80211_TESTMODE_STA_STATISTICS_IRQ_ISR_CNT,
    NL80211_TESTMODE_STA_STATISTICS_IRQ_ISR_PASS_CNT,
    NL80211_TESTMODE_STA_STATISTICS_IRQ_TASK_CNT,
    NL80211_TESTMODE_STA_STATISTICS_IRQ_AB_CNT,
    NL80211_TESTMODE_STA_STATISTICS_IRQ_SW_CNT,
    NL80211_TESTMODE_STA_STATISTICS_IRQ_TX_CNT,
    NL80211_TESTMODE_STA_STATISTICS_IRQ_RX_CNT,

    NL80211_TESTMODE_STA_STATISTICS_RESERVED_ARRAY,

    NL80211_TESTMODE_STA_STATISTICS_NUM,
    NL80211_TESTMODE_STA_STATISTICS_MAX = NL80211_TESTMODE_STA_STATISTICS_NUM - 1
};

enum mtk_nl80211_vendor_subcmd {
    MTK_SUBCMD_STRING_CMD = 0x2454,
};

enum mtk_string_attribute { STRING_ATTRIBUTE_DATA = 1 };

typedef enum _ENUM_TRAFFIC_CLASS_INDEX_T {
    TC0_INDEX = 0,
    TC1_INDEX,
    TC2_INDEX,
    TC3_INDEX,
    TC_DATA_NUM
} ENUM_TRAFFIC_CLASS_INDEX_T;

struct wpa_driver_sta_statistics_s {
    u8 version;
    u8 addr[ETH_ALEN];
    u32 flag;

    u32 link_score;
    u8 per;
    int rssi;
    u32 phy_mode;
    double tx_rate;

    u32 tx_total_cnt;
    u32 enqueue_total_cnt;
    u32 dequeue_total_cnt;
    u32 enqueue_sta_total_cnt;
    u32 dequeue_sta_total_cnt;
    u32 tx_exc_threshold_cnt;

    u32 tx_avg_process_time;
    u32 tx_max_process_time;
    u32 tx_avg_hif_process_time;
    u32 tx_max_hif_process_time;

    u32 tx_fail_cnt;
    u32 tx_timeout_cnt;
    u32 tx_avg_air_time;

    u32 tc_buf_full_cnt[TC_DATA_NUM];
    u32 tc_que_len[TC_DATA_NUM];

    /*
     * how many TC[0-3] resource back from firmware during
     * statistics intervals
     */
    u32 tc_back_count[TC_DATA_NUM];

    /*
     * how many times that no TC[0-3] resource when dequeue
     * statistics intervals
     */
    u32 dequeue_no_tc_res[TC_DATA_NUM];
    u32 tc_wanted_res[TC_DATA_NUM];
    u32 tc_used_res[TC_DATA_NUM];

    /*
     * wlan interrupt info
     * statistics intervals
     */
    u32 isr_cnt;
    u32 isr_pass_cnt;
    u32 isr_task_cnt;
    u32 isr_ab_cnt;
    u32 isr_sw_cnt;
    u32 isr_tx_cnt;
    u32 isr_rx_cnt;

    u32 tc_avg_que_len[TC_DATA_NUM];
    u32 tc_cur_que_len[TC_DATA_NUM];

    u8 reserved[32];
};

struct wpa_driver_cmd_reply_s {
    u32 reply_buf_size;
    u32 reply_len;
    union _reply_buf {
        char* ptr;
        u64 data;
    } reply_buf;
};

struct wpa_driver_test_mode_info {
    u32 index;
    u32 buflen;
};

struct wpa_driver_testmode_params {
    struct wpa_driver_test_mode_info hdr;
    u8* buf;
};

struct wpa_driver_get_sta_statistics_params {
    struct wpa_driver_test_mode_info hdr;
    u32 version;
    u32 flag;
    u8 addr[ETH_ALEN];
    u8* buf;
};

struct wpa_driver_p2p_sigma_params {
    struct wpa_driver_test_mode_info hdr;
    u32 idx;
    u32 value;
};

/* SW CMD */
struct wpa_driver_sw_cmd_params {
    struct wpa_driver_test_mode_info hdr;
    u8 set;
    u32 adr;
    u32 data;
};

struct wpa_driver_suspendmode_params {
    struct wpa_driver_test_mode_info hdr;
    u8 suspend;
};

struct wpa_pmkid_entry {
    u8 bssid[ETH_ALEN];
    u8 sta[ETH_ALEN];
    u8 pmkid[PMKID_LEN];
    u8 addremove; /*1- ADD, 0- Remove*/
};

struct wpa_driver_pmkid_entry {
    struct wpa_driver_test_mode_info hdr;
    u8 bssid[ETH_ALEN];
    u8 sta[ETH_ALEN];
    u8 pmkid[PMKID_LEN];
    u8 addremove; /*1- ADD, 0- Remove*/
};

enum nl80211_testmode_params {
    /* Old test mode command id, compatible with exist testmode command */
    NL80211_TESTMODE_SW_CMD = 1,
    NL80211_TESTMODE_STATISTICS = 0x10,

    /* New test mode command id, should greater than TESTMODE_CMD_ID_NEW_BEGIN */
    NL80211_TESTMODE_SUSPEND = 101,
    NL80211_TESTMODE_UPDATE_STA_PMKID = 1000
};

enum mtk_nl80211_vendor_subcmds {
    WIFI_EVENT_GENERIC_RESPONSE = 10,
};

enum mtk_generic_response_element {
    MTK_GRID_MANAGE_CHANNEL_LIST,  /* 0 */
    MTK_GRID_HANG_INFO,            /* 1 */
    MTK_GRID_SWPIS_BCN_INFO,       /* 2 */
    MTK_GRID_SWPIS_BCN_INFO_ABORT, /* 3 */
    MTK_GRID_EXTERNAL_AUTH,        /* 4 */
};

struct mtk_externa_auth_info {
    uint8_t ssid[SSID_MAX_LEN + 1];
    uint8_t ssid_len;
    uint8_t bssid[ETH_ALEN];
    uint32_t key_mgmt_suite;
    uint32_t action;
    uint8_t dot11MultiLinkActivated;
    uint8_t own_ml_addr[ETH_ALEN];
    uint8_t peer_ml_addr[ETH_ALEN];
} STRUCT_PACKED;

#endif
