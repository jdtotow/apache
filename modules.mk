mod_datanoesis.la: mod_datanoesis.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_datanoesis.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_datanoesis.la
