/*
 * Copyright (c) Hunan Goke,Chengdu Goke,Shandong Goke. 2021. All rights reserved.
 */

#ifndef __ETH_GOKE_FEMAC_H__
#define __ETH_GOKE_FEMAC_H__

/* MAC control register list */
#define MAC_PORTSEL                0x0200
#define MAC_PORTSEL_STAT_CPU       BIT(0)
#define MAC_PORTSEL_RMII           BIT(1)
#define MAC_PORTSET                0x0208
#define MAC_PORTSET_DUPLEX_FULL    BIT(0)
#define MAC_PORTSET_LINKED         BIT(1)
#define MAC_PORTSET_SPEED_100M     BIT(2)
#define MAC_SET                    0x0210
#define MAX_FRAME_SIZE             1600
#define MAX_FRAME_SIZE_MASK        GENMASK(10, 0)
#define BIT_PAUSE_EN               BIT(18)
#define RX_COALESCE_SET            0x0340
#define RX_COALESCED_FRAME_OFFSET  24
#define RX_COALESCED_FRAMES        8
#define RX_COALESCED_TIMER         0x74
#define QLEN_SET                   0x0344
#define RX_DEPTH_OFFSET            8
#define MAX_HW_FIFO_DEPTH          64
#define HW_TX_FIFO_DEPTH           12
#define HW_RX_FIFO_DEPTH           (MAX_HW_FIFO_DEPTH - HW_TX_FIFO_DEPTH)
#define FC_LEVEL                   0x0348
#define BITS_FC_ACTIVE_THR_OFFSET  8
#define FC_DEACTIVE_THR_MASK       GENMASK(5, 0)
#define FC_ACTIVE_THR_MASK         GENMASK(13, 8)
#define BIT_FC_EN                  BIT(14)
#define IQFRM_DES                  0x0354
#define RX_FRAME_LEN_MASK          GENMASK(11, 0)
#define BITS_PAYLOAD_ERR_OFFSET    28
#define BITS_PAYLOAD_ERR_MASK      0x1
#define BITS_HEADER_ERR_OFFSET     29
#define BITS_HEADER_ERR_MASK       0x1
#define BITS_PAYLOAD_DONE_OFFSET   30
#define BITS_PAYLOAD_DONE_MASK     0x1
#define BITS_HEADER_DONE_OFFSET    31
#define BITS_HEADER_DONE_MASK      0x1
#define IQ_ADDR                    0x0358
#define EQ_ADDR                    0x0360
#define EQFRM_LEN                  0x0364
#define ADDRQ_STAT                 0x036C
#define TX_CNT_INUSE_MASK          GENMASK(5, 0)
#define BIT_TX_READY               BIT(24)
#define BIT_RX_READY               BIT(25)
#define RX_COE_CTRL                0x0380
#define BIT_COE_IPV6_UDP_ZERO_DROP BIT(13)
#define BIT_COE_PAYLOAD_DROP       BIT(14)
#define BIT_COE_IPHDR_DROP         BIT(15)
#define COE_ERR_DROP               (BIT_COE_IPHDR_DROP |  \
									BIT_COE_PAYLOAD_DROP |  \
									BIT_COE_IPV6_UDP_ZERO_DROP)
#define TSO_DBG_EN      0x03A4
#define BITS_TSO_DBG_EN BIT(31)
#define TSO_DBG_STATE   0x03A8
#define TSO_DBG_ADDR    0x03AC
#define TSO_DBG_TX_INFO 0x03B0
#define TSO_DBG_TX_ERR  0x03B4
/* global control register list */
#define GLB_HOSTMAC_L32       0x0000
#define GLB_HOSTMAC_H16       0x0004
#define GLB_SOFT_RESET        0x0008
#define SOFT_RESET_ALL        BIT(0)
#define GLB_FWCTRL            0x0010
#define FWCTRL_VLAN_ENABLE    BIT(0)
#define FWCTRL_FW2CPU_ENA     BIT(5)
#define FWCTRL_FWALL2CPU      BIT(7)
#define GLB_MACTCTRL          0x0014
#define MACTCTRL_UNI2CPU      BIT(1)
#define MACTCTRL_MULTI2CPU    BIT(3)
#define MACTCTRL_BROAD2CPU    BIT(5)
#define MACTCTRL_MACT_ENA     BIT(7)
#define GLB_IRQ_STAT          0x0030
#define GLB_IRQ_ENA           0x0034
#define IRQ_ENA_PORT0_MASK    GENMASK(7, 0)
#define IRQ_ENA_PORT0         BIT(18)
#define IRQ_ENA_ALL           BIT(19)
#define GLB_IRQ_RAW           0x0038
#define IRQ_INT_RX_RDY        BIT(0)
#define IRQ_INT_TX_PER_PACKET BIT(1)
#define IRQ_INT_TX_FIFO_EMPTY BIT(6)
#define IRQ_INT_MULTI_RXRDY   BIT(7)
#define INT_TX_ERR            BIT(8)
#define DEF_INT_MASK          (IRQ_INT_MULTI_RXRDY |  \
							   IRQ_INT_TX_PER_PACKET |  \
							   IRQ_INT_TX_FIFO_EMPTY)
#define GLB_MAC_L32_BASE        0x0100
#define GLB_MAC_H16_BASE        0x0104
#define MACFLT_HI16_MASK        GENMASK(15, 0)
#define BIT_MACFLT_ENA          BIT(17)
#define BIT_MACFLT_FW2CPU       BIT(21)
#define glb_mac_h16(reg)        (GLB_MAC_H16_BASE + ((reg) * 0x8))
#define glb_mac_l32(reg)        (GLB_MAC_L32_BASE + ((reg) * 0x8))
#define MAX_MAC_FILTER_NUM      8
#define MAX_UNICAST_ADDRESSES   2
#define MAX_MULTICAST_ADDRESSES (MAX_MAC_FILTER_NUM - MAX_UNICAST_ADDRESSES)
/* software tx and rx queue number, should be power of 2 */
#define TXQ_NUM                64
#define RXQ_NUM                128
#define FEMAC_POLL_WEIGHT      64
#define HW_CAP_TSO             BIT(0)
#define HW_CAP_RXCSUM          BIT(1)
#define has_tso_cap(hw_cap)    ((hw_cap) & HW_CAP_TSO)
#define has_rxcsum_cap(hw_cap) ((hw_cap) & HW_CAP_RXCSUM)
#define RXBUF_ADDR_ALIGN_SIZE  64UL
/* UDP header len is 2 word */
#define UDP_HDR_LEN 2
/* IPv6 header len is 10 word */
#define IPV6_HDR_LEN 10
#define WORD_TO_BYTE 4

#define BIT_OFFSET_NFRAGS_NUM      11
#define BIT_OFFSET_PROT_HEADER_LEN 16
#define BIT_OFFSET_IP_HEADER_LEN   20
#define BIT_FLAG_SG                BIT(26)
#define BIT_FLAG_TXCSUM            BIT(27)
#define BIT_FLAG_UDP               BIT(28)
#define BIT_FLAG_IPV6              BIT(29)
#define BIT_FLAG_VLAN              BIT(30)
#define BIT_FLAG_TSO               BIT(31)

#define PHY_RESET_DELAYS_PROPERTY "goke,phy-reset-delays-us"

/*
 * The threshold for activing tx flow ctrl.
 * When the left amount of receive queue descriptors is below this threshold,
 * hardware will send pause frame immediately.
 * We advise this value is set between 1 and 10.
 * Too bigger is not a good choice.
 * This value must be smaller than tx flow ctrl deactive threshold.
 */
#define TX_FLOW_CTRL_ACTIVE_THRESHOLD 3
/*
 * The threshold for deactiving tx flow ctrl.
 * When the left amount of receive queue descriptors is
 * above or equal with this threshold,
 * hardware will exit flow control state.
 * We advise this value is set between 1 and 10.
 * Too bigger is not a good choice.
 * This value must be larger than tx flow ctrl active threshold.
 */
#define TX_FLOW_CTRL_DEACTIVE_THRESHOLD 5
#define FC_ACTIVE_MIN                   1
#define FC_ACTIVE_DEFAULT               3
#define FC_ACTIVE_MAX                   31
#define FC_DEACTIVE_MIN                 1
#define FC_DEACTIVE_DEFAULT             5
#define FC_DEACTIVE_MAX                 31

#ifdef CONFIG_FEPHY_OPT
/* FEPHY register list */

#define  SYS_REG_ADDR                   0x12028000
#define  FEPHY_TRIM_CACHE               0x3022
#define  FEPHY_TRIM_VALUE               0x20a1
#define  LOW_TEM_VALUE                  117
#define  HIGH_TEM_VALUE                 915
#define  LINK_STATUS                    0x4
#define  IS_LINK                        0X4
#define  SPEED_STATUS                   0x18
#define  SPEED_100M                     0x8
#define  LINK_AN_SR                     0x11
#define  MISC_CTRL45                    0x00B4
#define  MISC_CTRL47                    0x00BC
#define  MISC_CTRL48                    0x00C0
#define  TSENSOR_RESULT0                0x3ff
#define  TSENSOR_RESULT1                0x3ff0000
#define  TSENSOR_RESULT2                0x3ff
#define  TSENSOR_RESULT3                0x3ff0000
#define  TSENSOR_EN                     0xc3200000
#define  HIGH_TEMP                      100
#define  NORMAL_TEMP1                   90
#define  NORMAL_TEMP2                   20
#define  LOW_TEMP                       10
#define  TSENSOR_LIMIT                  0xfffff
#define  regval_to_temp(val)            ((val - 117) * 165 / 798 - 40)
#define  FEPHY_OPT_TIMER                (30 * HZ)
#endif

enum phy_reset_delays {
	PRE_DELAY,
	PULSE,
	POST_DELAY,
	DELAYS_NUM,
};

struct femac_queue {
	struct sk_buff **skb;
	dma_addr_t *dma_phys;
	unsigned int num;
	unsigned int head;
	unsigned int tail;
};

struct femac_tx_desc_ring {
	struct tx_desc *desc;
	dma_addr_t dma_phys;
};

#define FEMAC_RX_REFILL_IN_IRQ

struct femac_priv {
	void __iomem *port_base;
	void __iomem *glb_base;
	struct clk *clk;
	struct reset_control *mac_rst;
	struct reset_control *phy_rst;
	u32 phy_reset_delays[DELAYS_NUM];
	u32 link_status;

#ifdef CONFIG_FEPHY_OPT
	struct delayed_work watchdog_queue;
#endif
	struct device *dev;
	struct net_device *ndev;

	u32 hw_cap;
	struct femac_queue txq;
	struct femac_queue rxq;
#ifdef FEMAC_RX_REFILL_IN_IRQ
	struct sk_buff_head rx_head;
	spinlock_t rxlock;
#endif
	struct femac_tx_desc_ring tx_ring;
	u32 tx_fifo_used_cnt;
	struct napi_struct napi;

	/* 802.3x flow control */
	bool tx_pause_en;
	u32 tx_pause_active_thresh;
	u32 tx_pause_deactive_thresh;
};

struct frags_info {
	/* Word(2*i+2) */
	u32 addr;
	/* Word(2*i+3) */
	u32 size : 16;
	u32 reserved : 16;
};

struct tx_desc {
	/* Word0 */
	u32 total_len : 17;
	u32 reserv : 15;
	/* Word1 */
	u32 ipv6_id;
	/* Word2 */
	u32 linear_addr;
	/* Word3 */
	u32 linear_len : 16;
	u32 reserv3 : 16;
	/* MAX_SKB_FRAGS is 30 */
	struct frags_info frags[30];
};

#endif
