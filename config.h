/* See LICENSE file for copyright and license details. */

static const char name[]        = "tabbed-alacritty";

/* appearance */
static const char font[]        = "Fira Code:size=11";
static const char* normbgcolor  = "#222222";
static const char* normfgcolor  = "#cccccc";
static const char* selbgcolor   = "#555555";
static const char* selfgcolor   = "#ffffff";
static const char* urgbgcolor   = "#111111";
static const char* urgfgcolor   = "#cc0000";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = INT_MAX / 2;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY ControlMask
#define SHIFT ShiftMask

static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|SHIFT,     XK_t,      focusonce,   { 0 } },
	{ MODKEY|SHIFT,     XK_t,      spawn,       { 0 } },

	{ MODKEY,               XK_Tab,    rotate,      { .i = +1 } },
	{ MODKEY|SHIFT,     XK_Tab,    rotate,      { .i = -1 } },
	{ MODKEY|SHIFT,     XK_Left,   movetab,     { .i = -1 } },
	{ MODKEY|SHIFT,     XK_Right,  movetab,     { .i = +1 } },

	/* { MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") }, */
	{ MODKEY|SHIFT,               XK_1,      move,        { .i = 0 } },
	{ MODKEY|SHIFT,               XK_2,      move,        { .i = 1 } },
	{ MODKEY|SHIFT,               XK_3,      move,        { .i = 2 } },
	{ MODKEY|SHIFT,               XK_4,      move,        { .i = 3 } },
	{ MODKEY|SHIFT,               XK_5,      move,        { .i = 4 } },
	{ MODKEY|SHIFT,               XK_6,      move,        { .i = 5 } },
	{ MODKEY|SHIFT,               XK_7,      move,        { .i = 6 } },
	{ MODKEY|SHIFT,               XK_8,      move,        { .i = 7 } },
	{ MODKEY|SHIFT,               XK_9,      move,        { .i = 8 } },
	{ MODKEY|SHIFT,               XK_0,      move,        { .i = 9 } },

	{ MODKEY|SHIFT,               XK_q,      killclient,  { 0 } },

	{ MODKEY|SHIFT,               XK_grave,  focusurgent, { 0 } },
	/* { MODKEY,                     XK_grave,  toggle,      { .v = (void*) &urgentswitch } }, */

	{ 0,                    XK_F11,    fullscreen,  { 0 } },
};

