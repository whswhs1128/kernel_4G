/*
 * Copyright (c) Hunan Goke,Chengdu Goke,Shandong Goke. 2021. All rights reserved.
 */

#ifndef	__GOKE_CLK_H
#define	__GOKE_CLK_H

#include <linux/clk-provider.h>
#include <linux/io.h>
#include <linux/spinlock.h>

struct platform_device;

struct gk_clock_data {
	struct clk_onecell_data	clk_data;
	void __iomem		*base;
};

struct gk_fixed_rate_clock {
	unsigned int		id;
	char			*name;
	const char		*parent_name;
	unsigned long		flags;
	unsigned long		fixed_rate;
};

struct gk_fixed_factor_clock {
	unsigned int		id;
	char			*name;
	const char		*parent_name;
	unsigned long		mult;
	unsigned long		div;
	unsigned long		flags;
};

struct gk_mux_clock {
	unsigned int		id;
	const char		*name;
	const char		*const *parent_names;
	u8			num_parents;
	unsigned long		flags;
	unsigned long		offset;
	u8			shift;
	u8			width;
	u8			mux_flags;
	u32			*table;
	const char		*alias;
};

struct gk_gate_clock {
	unsigned int		id;
	const char		*name;
	const char		*parent_name;
	unsigned long		flags;
	unsigned long		offset;
	u8			bit_idx;
	u8			gate_flags;
	const char		*alias;
};

struct gk_clock_data *gk_clk_init(struct device_node *, int);
int gk_clk_register_fixed_rate(const struct gk_fixed_rate_clock *,
				int, struct gk_clock_data *);
int gk_clk_register_fixed_factor(const struct gk_fixed_factor_clock *,
				int, struct gk_clock_data *);
int gk_clk_register_mux(const struct gk_mux_clock *, int,
				struct gk_clock_data *);
int gk_clk_register_gate(const struct gk_gate_clock *,
				int, struct gk_clock_data *);

#define gk_clk_unregister(type) \
static inline \
void gk_clk_unregister_##type(const struct gk_##type##_clock *clks, \
				int nums, struct gk_clock_data *data) \
{ \
	struct clk **clocks = data->clk_data.clks; \
	int i; \
	for (i = 0; i < nums; i++) { \
		int id = clks[i].id; \
		if (clocks[id])  \
			clk_unregister_##type(clocks[id]); \
	} \
}

gk_clk_unregister(fixed_rate)
gk_clk_unregister(fixed_factor)
gk_clk_unregister(mux)
gk_clk_unregister(gate)

#endif	/* __GOKE_CLK_H */
