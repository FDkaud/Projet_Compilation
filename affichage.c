#include "affichage.h"

void affichage(int c, int* uc)
{
	switch(display_mode)
	{
		case XML_DISPLAY:
			consommer(c,uc,trace_xml);
			break;
		default:
			consommer(c,uc,trace_xml);
			break;
	}
}
