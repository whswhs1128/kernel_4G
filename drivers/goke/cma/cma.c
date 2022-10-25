/*
 * Copyright (c) Hunan Goke,Chengdu Goke,Shandong Goke. 2021. All rights reserved.
 */
#include <linux/goke_cma.h>

static u32 num_zones;
static struct cma_zone zone[ZONE_MAX];
static int use_bootargs;

unsigned int get_cma_size(void)
{
	int i;
	u64 total = 0;

	for (i = 0; i < num_zones; i++) {
		total += zone[i].nbytes;
	}

	/* unit is M */
	return (unsigned int)(total >> 20);
}

int is_cma_address(phys_addr_t phys, unsigned long size)
{
	phys_addr_t start, end;
	int i;

	for (i = 0; i < num_zones; i++) {
		start = zone[i].phys_start;
		end = zone[i].phys_start + zone[i].nbytes;

		if ((phys >= start) && ((phys + size) <= end)) {
			/*
			 * Yes, found!
			 */
			return 1;
		}
	}

	return 0;
}
EXPORT_SYMBOL(is_cma_address);

static int __init mmz_parse_cmdline(char *s)
{
	char *line = NULL;
	char *tmp = NULL;
	char tmpline[256];

	if (s == NULL) {
		pr_info("There is no cma zone!\n");
		return 0;
	}
	strncpy(tmpline, s, sizeof(tmpline));
	tmpline[sizeof(tmpline) - 1] = '\0';
	tmp = tmpline;

	while ((line = strsep(&tmp, ":")) != NULL) {
		int i;
		char *argv[6];

		for (i = 0; (argv[i] = strsep(&line, ",")) != NULL;)
			if (++i == ARRAY_SIZE(argv)) {
				break;
			}

		zone[num_zones].pdev.coherent_dma_mask = DMA_BIT_MASK(64);
		if (i == 4) {
			strlcpy(zone[num_zones].name, argv[0], NAME_LEN_MAX);
			zone[num_zones].gfp = memparse(argv[1], NULL);
			zone[num_zones].phys_start = memparse(argv[2], NULL);
			zone[num_zones].nbytes = memparse(argv[3], NULL);
		}

		else if (i == 6) {
			strlcpy(zone[num_zones].name, argv[0], NAME_LEN_MAX);
			zone[num_zones].gfp = memparse(argv[1], NULL);
			zone[num_zones].phys_start = memparse(argv[2], NULL);
			zone[num_zones].nbytes = memparse(argv[3], NULL);
			zone[num_zones].alloc_type = memparse(argv[4], NULL);
			zone[num_zones].block_align = memparse(argv[5], NULL);
		} else {
			pr_err("ion parameter is not correct\n");
			continue;
		}

		num_zones++;
	}
	if (num_zones != 0) {
		use_bootargs = 1;
	}

	return 0;
}
early_param("mmz", mmz_parse_cmdline);

phys_addr_t goke_get_zones_start(void)
{
	int i;
	phys_addr_t lowest_zone_base = memblock_end_of_DRAM();

	for (i = 0; i < num_zones; i++) {
		if (lowest_zone_base > zone[i].phys_start) {
			lowest_zone_base = zone[i].phys_start;
		}
	}

	return lowest_zone_base;
}
EXPORT_SYMBOL(goke_get_zones_start);

struct cma_zone *goke_get_cma_zone(const char *name)
{
	int i = 0;

	for (i = 0; i < num_zones; i++)
		if (strcmp(zone[i].name, name) == 0) {
			break;
		}

	if (i == num_zones) {
		return NULL;
	}

	return &zone[i];
}
EXPORT_SYMBOL(goke_get_cma_zone);

struct device *goke_get_cma_device(const char *name)
{
	int i = 0;

	for (i = 0; i < num_zones; i++)
		if (strcmp(zone[i].name, name) == 0) {
			break;
		}

	if (i == num_zones) {
		return NULL;
	}

	return &zone[i].pdev;
}
EXPORT_SYMBOL(goke_get_cma_device);

int __init goke_declare_heap_memory(void)
{
	int i;
	int ret = 0;

	if (use_bootargs == 0) {
		pr_info("cma zone is not set!\n");
		return ret;
	}

	for (i = 0; i < num_zones; i++) {
		ret = dma_declare_contiguous(&zone[i].pdev,
					     zone[i].nbytes, zone[i].phys_start, 0);
		if (ret) {
			panic("declare cma zone %s base: %lux size:%lux MB failed. ret:%d",
			      zone[i].name, (unsigned long)zone[i].phys_start,
			      (unsigned long)zone[i].nbytes >> 20, ret);
		}
		zone[i].phys_start = cma_get_base(zone[i].pdev.cma_area);
		zone[i].nbytes = cma_get_size(zone[i].pdev.cma_area);

		/* FIXME need to fix dma_declare_contiguous return value &&value type */
	}

	return ret;
}
EXPORT_SYMBOL(goke_declare_heap_memory);

static int mmz_setup(struct reserved_mem *rmem)
{
	return 0;
}
RESERVEDMEM_OF_DECLARE(cma, "mmz", mmz_setup);
