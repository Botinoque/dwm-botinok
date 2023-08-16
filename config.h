
/* appearance */
static const unsigned int borderpx  		= 2;	/* border pixel of windows */
static const unsigned int snap      		= 1;	/* snap pixel */
static const unsigned int gappx			= 3;
static const unsigned int systraypinning 	= 0;	/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing 	= 2;	/* systray spacing */
static const int systraypinningfailfirst 	= 0;	/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        		= 1;	/* 0 means no systray */
static const int showbar            		= 1;	/* 0 means no bar */
static const int topbar             		= 1;	/* 0 means bottom bar */
static const int focusedontop       		= 1;	/* 1 means focused client is shown on top of floating windows */
static const char *fonts[]          		= { "Terminus:size=12" };
/* static const char dmenufont[]       		= "Terminus:size=14"; */
static const char col_darkgray[]       		= "#2c2c2c";
static const char col_mediumgray[]     		= "#444444";
static const char col_lightgray[]      		= "#bbbbbb";
static const char col_black[]       		= "#000000";
static const char col_select[]        		= "#00ff00";
static const char *colors[][3]      		= {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_lightgray, col_darkgray, col_mediumgray },
	[SchemeSel]  = { col_black, col_select,  col_select  },
};

/* tagging */
static const char *tags[] = { "main", "firefox", "music" };

#define WTYPE "_NET_WM_WINDOW_TYPE_"
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	
	/* class      		role 	instance 	title 		wintype,          	tags mask  		switchtotag 	isfloating	alwaysontop	monitor	 */
	{ NULL,       		NULL,	NULL,		NULL,		WTYPE "DIALOG",   	0,         		0,		1,		1 },
	{ NULL,       		NULL,	NULL,		NULL,		WTYPE "UTILITY",  	0,         		0,		1,		1 },
	{ NULL,       		NULL,	NULL,		NULL,		WTYPE "TOOLBAR",  	0,         		0,		1,		1 },
	{ NULL,       		NULL,	NULL,		NULL,		WTYPE "SPLASH",   	0,         		0,		1,		1 },
	{ "Gimp",     		NULL,	NULL,		NULL,		NULL,			1,         		1,		1,		0 },
	{ "Thunar",		NULL,	NULL,		NULL,		NULL,		 	1,			1,		0,		0 },
	{ "Firefox",  		NULL,	NULL,		NULL,		NULL,		 	1 << 1,			1,		0,		0 },
	{ "firefox",  		NULL,	NULL,		NULL,		NULL,		 	1 << 1,			1,		0,		0 },
	{ "Galculator", 	NULL,	NULL,		NULL,		NULL,		  	1,			1,		1,		0 },
	{ "Audacious", 		NULL, 	NULL,		NULL,		NULL,		  	1 << 2,			1,		1,  		0 },
	{ "mpv",		NULL,  	NULL,		NULL,		NULL,			1,			1,		0,		0 },
	{ "smplayer",		NULL,  	NULL,		NULL,		NULL,			1,			1,		0,		0 },
	{ "Sakura",		NULL,  	NULL,		NULL,		NULL,			1,			1,		0,		0 }, 
	{ "Pavucontrol",	NULL,	NULL,		NULL,		NULL,			1 << 2,			1,		1,		0 },
	{ "Blueman",		NULL,	NULL,		NULL,		NULL,			1 << 2,			1,		1,		0 },
	{ NULL,			NULL,	NULL,		"Network",	NULL,			0,			0,		1,		0 },
	{ NULL,			"pop-up", NULL,		NULL,		NULL,			0,			0,		1,		1 },
	{ NULL,			NULL,	NULL,		"Progress",	NULL,			0,			0,		1,		0 },
	{ NULL,			NULL,	NULL,		"Task Manager",	NULL,			0,			0,		1,		0 },
	{ NULL,			NULL,	NULL,		"Execute File", NULL,			0,			0,		1,		0 },
	{ "qutebrowser",	NULL,	NULL,		NULL,		NULL,			1 << 1,			1,		0,		0 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "G",      grid },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
	{ "T",	    tile },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
/* static char dmenumon[2] = "0";  component of menucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_darkgray, "-nf", col_lightgray, "-sb", col_select, "-sf", col_darkgray, topbar ? NULL : "-b", NULL };
*/
static const char *termcmd[]  = { "alacritty", NULL };
static const char *thunarcmd[] = { "pcmanfm", NULL }; 
static const char *audaciouscmd[] = { "audacious", NULL };
static const char *wikipedia[] = { "sh", "/work/wikipedia/fbpanel.sh", NULL };
static const char *anki[] = { "anki", NULL };
static const char *taskmngr[] = { "lxtask", NULL };
static const char *qutebrowser[] = { "qutebrowser", NULL };
static const char *internetcmd[] = { "sh", "/home/botinok/scripts/internet.sh", NULL };
/* static const char *internetcmd[] = {"alacritty", NULL }; */


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			XK_c,	   spawn,	   {.v = termcmd } },	
	{ MODKEY,			XK_z,	   spawn,	   {.v = audaciouscmd } },
	{ MODKEY,			XK_v,	   spawn,	   {.v = thunarcmd } },
	{ MODKEY,			XK_e,	   spawn,	   {.v = qutebrowser } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ Mod1Mask,                     XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask, 	        	XK_F4,     killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,			XK_g,	   setlayout,	   {.v = &layouts[0]} },
	{ MODKEY,			XK_space,  togglefloating, {0} },
	{ MODKEY,			XK_n,	   togglefullscreen, {0} },
	{ MODKEY,			XK_a,		spawn,		{.v = internetcmd } },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,		0,		Button1,	setlayout,	{0} },
	{ ClkLtSymbol,		0,		Button3,	setlayout,	{.v = &layouts[2]} },
	{ ClkWinTitle,		0,		Button2,	zoom,		{0} },
	{ ClkStatusText,	0,		Button2,	spawn,		{.v = wikipedia } },
	{ ClkStatusText,	0,		Button3,	spawn,		{.v = audaciouscmd } },
	{ ClkStatusText,	0,		Button1,	killclient,	{0} },
	{ ClkStatusText,	0,		Button4,	spawn,		{.v = anki} },
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,	{0} },
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating,	{0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,		Button1,	view,		{0} },
	{ ClkTagBar,		0,		Button3,	toggleview,	{0} },
	{ ClkTagBar,		MODKEY,		Button1,	tag,		{0} },
	{ ClkTagBar,		MODKEY,		Button3,	toggletag,	{0} },
	{ ClkWinTitle,		0,		Button1,	togglefloating,	{0} },
	{ ClkWinTitle,		0,		Button4,	focusstack,	{.i = +1} },
	{ ClkWinTitle,		0,		Button5,	focusstack,	{.i = -1} },
	{ ClkRootWin,		0,		Button2,	spawn,		{.v = qutebrowser } },
	{ ClkRootWin,		0,		Button3,	spawn,		{.v = taskmngr } },
};


