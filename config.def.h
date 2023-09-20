/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
#include "/home/olidiaks/.cache/wal/colors-wal-dwm.h"
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "st-256color",      NULL,     "st",           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
  { "[@]",      spiral },  /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
  { "[\\]",      dwindle },
};

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STCMD(cmd) { .v = (const char*[]){ "st", "-t", scratchpadname, "-g", "120x34", "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", "-e","tmux", NULL };

static const Key keys[] = {
	/* modifier                     key         function        argument */
	{ MODKEY,                       XK_d,                       spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                  spawn,                  {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,                  togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY,			XK_F8,			spawn,		{.v = (const char*[]){ "toogle_touchpad", NULL } } },
	{ MODKEY,			XK_F9,			spawn,		{.v = (const char*[]){ "mounter", NULL } } },
	{ MODKEY,			XK_F10,			spawn,		{.v = (const char*[]){ "unmounter", NULL } } },
	{ 0,                            XF86XK_Calculator,          togglescratch,          STCMD("python")},
	{ 0,                            XK_Print,                   spawn,                  SHCMD("flameshot screen")},
  { MODKEY,                     XK_Print,                   spawn,                  SHCMD("flameshot gui")},
  { MODKEY,                       XK_m,                       spawn,                  {.v = (const char*[]){"displaysetup", NULL}} },
  { MODKEY|ControlMask,           XK_b,                       spawn,                  {.v = (const char*[]){"brave-browser", NULL}}},
  { MODKEY|ControlMask,           XK_m,                       spawn,                  {.v = (const char*[]){"brave-browser","--app=https://www.facebook.com/messages", NULL}}},
  { MODKEY|ControlMask,           XK_d,                       spawn,                  {.v = (const char*[]){"brave-browser","--app=https://www.diki.pl", NULL}}},
	{ MODKEY|ControlMask,           XK_v,                       spawn,                  {.v = (const char*[]){"brave-browser","--app=https://uonetplus.vulcan.net.pl/warszawawola", NULL}}},
  { MODKEY|ControlMask,           XK_t,                       spawn,                  {.v = (const char*[]){"brave-browser","--app=https://teams.microsoft.com", NULL}}},
	{ MODKEY|ControlMask,           XK_c,                       spawn,                  {.v = (const char*[]){"brave-browser","--app=https://chat.openai.com", NULL}}},
  { MODKEY|ControlMask,           XK_w,                       spawn,                  {.v = (const char*[]){"libreoffice", "--writer", NULL}}},
  { MODKEY|ControlMask,           XK_n,                       spawn,                  {.v = (const char*[]){"thunar", NULL}}},
  { MODKEY|ControlMask,           XK_p,                       spawn,                  {.v = (const char*[]){"pavucontrol", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_a,                       spawn,                  SHCMD("wmname 'LG3D'; studio")},
  { MODKEY|ControlMask|Mod1Mask,  XK_w,                       spawn,                  {.v = (const char*[]){"webstorm", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_c,                       spawn,                  {.v = (const char*[]){"clion", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_h,                       spawn,                  {.v = (const char*[]){"phpstorm", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_y,                       spawn,                  {.v = (const char*[]){"pycharm", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_v,                       spawn,                  {.v = (const char*[]){"code", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_n,                       spawn,                  SHCMD("wmname 'LG3D'; netbeans")},
  { MODKEY|ControlMask,           XK_w,                       spawn,                  {.v = (const char*[]){"libreoffice --writer", NULL}}},
  { MODKEY|ControlMask,           XK_s,                       spawn,                  {.v = (const char*[]){"syncthing", NULL}}},
  { MODKEY|ControlMask|Mod1Mask,  XK_s,                       spawn,                  {.v = (const char*[]){"steam", NULL}}},
  { MODKEY|Mod1Mask,			XK_v,                       spawn,                  {.v = (const char*[]){"virt-manager", NULL}}},
//	{ MODKEY|Mod1Mask,              XK_s,                       spawn,                  {.v = (const char*[]){"brave-browser", "--app=https://open.spotify.com", NULL}}},
	{ MODKEY|Mod1Mask,              XK_s,                       spawn,                  {.v = (const char*[]){"spotify", NULL}}},
	{ MODKEY|Mod1Mask,              XK_m,                       spawn,                  {.v = (const char*[]){"signal-desktop", NULL}}},
	{ MODKEY,                       XK_f,                       setlayout,              {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_f,                       setlayout,              {.v = &layouts[0]} },
  { MODKEY,                       XK_p,                       spawn,                  {.v = (const char*[]){"dmenu-power-managment", NULL}}},
  { MODKEY|ShiftMask,             XK_n,                       spawn,                  {.v = (const char*[]){"killall", "nm-applet", NULL}}},
	{ MODKEY,                       XK_j,                       focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_space,                   zoom,                   {0} },
	{ MODKEY|ShiftMask,             XK_q,                       killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating,         {0} },
	{ MODKEY,                       XK_0,                       view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,               {.i = +1 } },
	{ MODKEY,                       XK_period,                  focusmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,                 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,                 {.i = -1 } },
	{ 0,                            XF86XK_AudioMute,		        spawn,		              SHCMD("volume_mute_toggle") },
	{ 0,                            XF86XK_AudioMicMute,		        spawn,		              SHCMD("volume_mute_toggle_mic") },
	{ 0,                            XF86XK_AudioRaiseVolume,	  spawn,		              SHCMD("volume_up") },
	{ 0,                            XF86XK_AudioLowerVolume,	  spawn,		              SHCMD("volume_down") },
  { 0,                            XF86XK_AudioPrev,		        spawn,		              {.v = (const char*[]){ "spt", "playback", "-n", NULL } } },
	{ 0,                            XF86XK_AudioNext,		        spawn,		              {.v = (const char*[]){ "spt", "playback", "-p", NULL } } },
	{ 0,                            XF86XK_AudioPlay,		        spawn,		              {.v = (const char*[]){ "spt", "playback", "-t", NULL } } },
//	{ 0,                            XF86XK_AudioStop,		        spawn,		              {.v = (const char*[]){ "spt", "playback", NULL } } },
	{ 0,                            XF86XK_MonBrightnessUp,	    spawn,		              {.v = (const char*[]){ "light", "-A", "5", NULL } } },
	{ 0,                            XF86XK_MonBrightnessDown,	  spawn,		              {.v = (const char*[]){ "light", "-U", "5", NULL } } },
	TAGKEYS(                        XK_1,                                               0)
	TAGKEYS(                        XK_2,                                               1)
	TAGKEYS(                        XK_3,                                               2)
	TAGKEYS(                        XK_4,                                               3)
	TAGKEYS(                        XK_5,                                               4)
	TAGKEYS(                        XK_6,                                               5)
	TAGKEYS(                        XK_7,                                               6)
	TAGKEYS(                        XK_8,                                               7)
	TAGKEYS(                        XK_9,                                               8)
	{ MODKEY,                       XK_q,                       quit,                   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

