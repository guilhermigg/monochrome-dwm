/* --- appearance --- */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "scientifica:size=12" };
static const char dmenufont[]       = "scientifica:size=14";

/* --- colors --- */
static const char background[]        = "#282c34";
static const char foreground[]        = "#bbc2cf";
static const char border[]   	      = "#ffffff";
static const char alt_foreground[]    = "#bbc2cf";
static const char alt_background[]    = "#1c1f24";

static const char *colors[][3]      = {

	/*  thing            fg                bg            border   */
	[SchemeNorm] = { foreground,      background,        border },
	[SchemeSel]  = { alt_foreground,  alt_background,    border },
};

/* --- tagging --- */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI" };

/* --- rules --- */
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
	{ "mpv",      NULL,       NULL,       0,            0,           -1 },
};

/* --- layouts --- */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

/* --- fibonacci's patch --- */
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",      spiral  },    /* first entry is default */
	{ "[Fl]",     NULL    },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[T]",      tile    },
 	{ "[D]",      dwindle },
};

/* --- key definitions --- */
#define MODKEY Mod4Mask /* super key */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* --- commands --- */

static const char *rofi[] = {"rofi", "-show", "run", "-modi", "file-browser"};
static const char *termcmd[] = {"st", NULL};
static const char *browser[] = {"chromium-browser", NULL};
static const char *screenshot[] = {"/home/smoek/src/print.sh", NULL};
static const char *emacs[] = {"emacs", NULL};

/*  --- mpc commands --- */
static const char *prev[] = {"mpc", "prev", NULL};
static const char *next[] = {"mpc", "next", NULL};
static const char *toggle[] = {"mpc", "toggle", NULL};

/* --- keybinds --- */
static Key keys[] = {

	/* modifier                     key        function        arguments */

	/* --- personal keybinds */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd}},
	{ MODKEY,                       XK_d,      spawn,          {.v = rofi}},
	{ MODKEY,                       XK_b,      spawn,          {.v = browser}},
	{ MODKEY,                       XK_p,      spawn,          {.v = screenshot}},
	{ MODKEY,                       XK_e,      spawn,          {.v = emacs}},

	/* --- mpd things --- */
	{ MODKEY,                       XK_Left,   spawn,          {.v = prev}},
	{ MODKEY,                       XK_Right,  spawn,          {.v = next}},
	{ MODKEY,                       XK_Down,   spawn,          {.v = toggle}},

	/* --- dmenu default keys --- */
	{ MODKEY,                       XK_n,      togglebar,      {0} }, /* hide/show dwm bar */

	/*  --- focus key */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_x,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },

	/*  --- resize/manage window --- */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

	/*  --- layouts --- */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/*  --- workspaces --- */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

