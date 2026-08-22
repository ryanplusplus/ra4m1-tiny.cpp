HARDWARE_MANUAL_URL := https://www.renesas.com/en/document/mah/renesas-ra4m1-group-users-manual-hardware?r=1054146
DATASHEET_URL := https://www.renesas.com/en/document/dst/ra4m1-group-datasheet?r=1054146

.PHONY: hardware_manual
hardware_manual:
	@`command -v xdg-open || echo open` $(HARDWARE_MANUAL_URL)

.PHONY: datasheet
datasheet:
	@`command -v xdg-open || echo open` $(DATASHEET_URL)
