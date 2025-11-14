# ALPS_KK_LogoLKCompress

![[proof.png]]

This tool is made to saving space of ALPS source code space for LK.

LK MTK customization waste space in logo area, as there are many logo for various size and China operator (Unicom, Telecom, Mobile).

For ALPS.KK1.MP7.V1 the logo total is 6.3GB

![[before_compress.png]]

This tool aims to economize space for git and save space in local disk with our tools. As result, we save 5.9GB, in total the folder is 302.4MB

![[after_compress.png]]

# Build

Compress:
```
gcc -o bmp_to_bmc compress.c minilzo.c
<Executing compress_all.sh <logo folder>>
```

Explain: compress raw data of BMP to LZO -> Delete all BMP

Decompress:
```
gcc -o bmc_to_bmp compress.c minilzo.c
<Copy the bmc_to_bmp to mediatek/custom/common/lk/logo_tool>
```

Must modify the rules.mk of logo:

```
LOCAL_DIR := $(GET_LOCAL_DIR)
BOOT_LOGO_DIR := $(LOCAL_DIR)
#$(info lk/logo/dir=$(LOCAL_DIR),builddir=$(BUILDDIR))

BMP_TO_RAW := $(BOOT_LOGO_DIR)/../logo_tool/bmp_to_raw
#20251114 logo is save space
BMC_TO_BMP := $(BOOT_LOGO_DIR)/../logo_tool/bmc_to_bmp
#20251114 logo is save space
ZPIPE := $(BOOT_LOGO_DIR)/../logo_tool/zpipe
            
$(info BMP_TO_RAW=$(BMP_TO_RAW))
#20251114 logo is save space
$(info BMC_TO_BMP=$(BMC_TO_BMP))
#20251114 logo is save space
$(info ZPIPE=$(ZPIPE))
$(info CUSTOM_LK_LOGO=$(CUSTOM_LK_LOGO))
$(info BOOT_LOGO_DIR =$(BOOT_LOGO_DIR))

BOOT_LOGO_RESOURCE := $(BUILDDIR)/$(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO).raw
LOGO_IMAGE := $(BUILDDIR)/logo.bin
RESOURCE_OBJ_LIST :=   \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_uboot.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_battery.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_low_battery.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_charger_ov.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_0.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_1.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_2.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_3.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_4.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_5.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_6.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_7.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_8.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_9.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_num_percent.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_01.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_02.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_03.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_04.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_05.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_06.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_07.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_08.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_09.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_animation_10.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_01.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_02.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_03.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_04.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_05.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_06.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_07.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_08.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_09.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_10_10.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_bg.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_img.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_bat_100.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_kernel.raw 

ifeq ($(strip $(MTK_PUMP_EXPRESS_SUPPORT)), yes)
RESOURCE_OBJ_LIST +=   \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_100.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_ani-01.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_ani-02.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_ani-03.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_ani-04.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_ani-05.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_ani-06.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_00.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_01.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_02.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_03.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_04.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_05.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_06.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_07.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_08.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_09.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_fast_charging_percent.raw 
endif

ifeq ($(strip $(MTK_WIRELESS_CHARGER_SUPPORT)), yes)
RESOURCE_OBJ_LIST +=   \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_00.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_01.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_02.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_03.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_04.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_05.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_06.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_07.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_08.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_09.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_num_percent.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_10_0.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_10_1.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_10_2.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_10_3.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_30_0.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_30_1.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_30_2.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_30_3.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_60_0.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_60_1.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_60_2.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_60_3.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_90_0.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_90_1.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_90_2.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_90_3.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_0.raw \
            $(BOOT_LOGO_DIR)/$(CUSTOM_LK_LOGO)_wireless_bat_100.raw 

endif  
                                      
GENERATED += \
            $(BOOT_LOGO_RESOURCE) \
            $(LOGO_IMAGE) \
            $(addprefix $(BUILDDIR)/,$(RESOURCE_OBJ_LIST))


all:: $(LOGO_IMAGE) 

$(LOGO_IMAGE):$(MKIMG) $(BOOT_LOGO_RESOURCE)
	$(NOECHO) if [ ! -x $(MKIMG) ]; then chmod a+x $(MKIMG); fi
	@echo "MKING $(LOGO_IMAGE)"
	$(MKIMG) $(BOOT_LOGO_RESOURCE) LOGO > $(LOGO_IMAGE)

$(BOOT_LOGO_RESOURCE): $(addprefix $(BUILDDIR)/,$(RESOURCE_OBJ_LIST)) $(ZPIPE)
	@$(MKDIR)
	$(NOECHO) if [ ! -x $(ZPIPE) ]; then chmod a+x $(ZPIPE); fi
	@echo "zpiping "
	$(ZPIPE) -l 9 $@ $(addprefix $(BUILDDIR)/,$(RESOURCE_OBJ_LIST))

#20251114 logo is save space
# 
# $(BUILDDIR)/%.raw: %.bmp $(BMP_TO_RAW)
# 	@$(MKDIR)
# 	$(NOECHO) if [ ! -x $(BMP_TO_RAW) ]; then chmod a+x $(BMP_TO_RAW); fi
# 	@echo "Compiling_BMP_TO_RAW $<"
# 	$(BMP_TO_RAW) $@ $<

$(BUILDDIR)/%.raw: %.bmc $(BMP_TO_RAW) $(BMC_DECOMPRESS)
	@$(MKDIR)
	$(NOECHO) if [ ! -x $(BMP_TO_RAW) ]; then chmod a+x $(BMP_TO_RAW); fi
	$(NOECHO) if [ ! -x $(BMC_DECOMPRESS) ]; then chmod a+x $(BMC_DECOMPRESS); fi
	@echo "Decompressing BMC $<"
	$(BMC_DECOMPRESS) $< $*.bmp
	@echo "Converting BMP to RAW $*.bmp"
	$(BMP_TO_RAW) $@ $*.bmp
	@echo "Cleaning up temporary BMP"
	$(NOECHO) rm -f $*.bmp
#20251114 logo is save space
```