#ifndef _CONFOPTIONS_H_
#define _CONFOPTIONS_H_

#include "c.h"


void		InitializeConfOptions(void);

bool		set_config_option(const char *name, const char *value);
void	   *get_config_option(const char *name);

extern double real_placeholder;

extern char *rtcfg_cluster_name;
extern char *rtcfg_conninfo;

extern char *pid_file;
extern char *archive_dir;

extern int	vac_frequency;
extern int	slon_log_level;
extern int	sync_interval;
extern int	sync_interval_timeout;
extern int	sync_max_rowsize;
extern int	sync_max_largemem;

extern int	sync_group_maxsize;
extern int	desired_sync_time;

extern int	quit_sync_provider;
extern int	quit_sync_finalsync;

char	   *Syslog_ident;
char	   *Syslog_facility;
int			Use_syslog;

bool		logpid;
bool		logtimestamp;
bool		drop_indices;
char	   *log_timestamp_format;
char	   *sql_on_connection;
char	   *lag_interval;

enum config_type
{
	SLON_C_BOOL,
	SLON_C_INT,
	SLON_C_REAL,
	SLON_C_STRING
};

struct config_generic
{
	/* constant fields, must be set correctly in initial value: */
	const char *name;
				const char *short_desc;
				const char *long_desc;
	enum config_type vartype;	/* type of variable (set only at startup) */
};


struct config_int
{
	struct config_generic gen;
	/* these fields must be set correctly in initial value: */
	/* (all but reset_val are constants) */
	int		   *variable;
	int			default_val;
	int			min;
	int			max;
};

struct config_bool
{
	struct config_generic gen;
	/* these fields must be set correctly in initial value: */
	/* (all but reset_val are constants) */
	bool	   *variable;
	bool		default_val;
};

struct config_real
{
	struct config_generic gen;
	/* these fields must be set correctly in initial value: */
	/* (all but reset_val are constants) */
	double	   *variable;
	double		default_val;
	double		min;
	double		max;
};

struct config_string
{
	struct config_generic gen;
	/* these fields must be set correctly in initial value: */
	/* (all are constants) */
	char	  **variable;
				const char *default_val;
};



static struct config_int ConfigureNamesInt[] =
{
	{
		{
			(const char *)"vac_frequency",		/* conf name */
			gettext_noop("Sets how many cleanup cycles to run before a vacuum is done"),		/* short desc */
			gettext_noop("Sets how many cleanup cycles to run before a vacuum is done"),		/* long desc */
			SLON_C_INT			/* config type */
		},
		&vac_frequency,			/* var name */
		3,						/* default val */
		0,						/* min val */
		100						/* max val */
	},
	{
		{
			(const char *)"log_level",
			gettext_noop("debug log level"),
			gettext_noop("debug log level"),
			SLON_C_INT
		},
		&slon_log_level,
		4,
		0,
		4
	},
	{
		{
			(const char *)"sync_interval",
			gettext_noop("sync event interval"),
			gettext_noop("sync event interval in ms"),
			SLON_C_INT
		},
		&sync_interval,
		2000,
		10,
		60000
	},
	{
		{
			(const char *)"sync_interval_timeout",
			gettext_noop("sync interval time out"),
			gettext_noop("sync interval time out"),
			SLON_C_INT
		},
		&sync_interval_timeout,
		10000,
		0,
		1200000
	},
	{
		{
			(const char *)"sync_group_maxsize",
			gettext_noop("sync group"),
			gettext_noop("sync group"),
			SLON_C_INT
		},
		&sync_group_maxsize,
		20,
		0,
		10000
	},
	{
		{
			(const char *)"desired_sync_time",
			gettext_noop("maximum time planned for grouped SYNCs"),
			gettext_noop("If replication is behind, slon will try to increase numbers of "
			  "syncs done targetting that they should take this quantity of "
						 "time to process"),
			SLON_C_INT
		},
		&desired_sync_time,
		60000,
		0,
		6000000
	},
#ifdef HAVE_SYSLOG
	{
		{
			(const char *)"syslog",
			gettext_noop("Uses syslog for logging."),
			gettext_noop("If this parameter is 1, messages go both to syslog "
						 "and the standard output. A value of 2 sends output only to syslog. "
			"(Some messages will still go to the standard output/error.) The "
						 "default is 0, which means syslog is off."),
			SLON_C_INT
		},
		&Use_syslog,
		0,
		0,
		2
	},
#endif
	{
		{
			(const char *)"quit_sync_provider",
			gettext_noop("Node to watch for a final SYNC"),
			gettext_noop("We want to terminate slon when the worker thread reaches a certain SYNC number "
					"against a certain provider.  This is the provider... "),
			SLON_C_INT
		},
		&quit_sync_provider,
		0,
		0,
		2147483647
	},
	{
		{
			(const char *)"quit_sync_finalsync",
			gettext_noop("SYNC number at which slon should abort"),
			gettext_noop("We want to terminate slon when the worker thread reaches a certain SYNC number "
				 "against a certain provider.  This is the SYNC number... "),
			SLON_C_INT
		},
		&quit_sync_finalsync,
		0,
		0,
		2147483647
	},
	{
		{
			(const char *)"sync_max_rowsize",		/* conf name */
			gettext_noop("sl_log_? rows larger than that are read separately"),		/* short desc */
			gettext_noop("sl_log_? rows larger than that are read separately"),		/* long desc */
			SLON_C_INT			/* config type */
		},
		&sync_max_rowsize,			/* var name */
		8192,						/* default val */
		1024,						/* min val */
		32768						/* max val */
	},
	{
		{
			(const char *)"sync_max_largemem",		/* conf name */
			gettext_noop("How much memory to allow for sl_log_? rows exceeding sync_max_rowsize"),		/* short desc */
			gettext_noop("How much memory to allow for sl_log_? rows exceeding sync_max_rowsize"),		/* long desc */
			SLON_C_INT			/* config type */
		},
		&sync_max_largemem,			/* var name */
		5242880,					/* default val */
		1048576,					/* min val */
		1073741824					/* max val */
	},
	{0}
};

static struct config_bool ConfigureNamesBool[] =
{
	{
		{
			(const char *)"log_pid",	/* conf name */
			gettext_noop("place holder"),		/* short desc */
			gettext_noop("place holder"),		/* long desc */
			SLON_C_BOOL			/* config type */
		},
		&logpid,				/* var_name */
		false					/* default_value */
	},
	{
		{
			(const char *)"log_timestamp",
			gettext_noop("place holder"),
			gettext_noop("place holder"),
			SLON_C_BOOL
		},
		&logtimestamp,
		true
	},

	{0}
};

static struct config_real ConfigureNamesReal[] =
{
	{
		{
			(const char *)"real_placeholder",	/* conf name */
			gettext_noop("place holder"),		/* short desc */
			gettext_noop("place holder"),		/* long desc */
			SLON_C_REAL			/* config type */
		},
		&real_placeholder,		/* var_name */
		0.0,					/* default val */
		0.0,					/* min_value */
		1.0						/* max value */
	},
	{0}
};

static struct config_string ConfigureNamesString[] =
{
	{
		{
			(const char *)"cluster_name",		/* conf name */
			gettext_noop("Name of the replication cluster"),	/* short desc */
			NULL,				/* long desc */
			SLON_C_STRING		/* config type */
		},
		&rtcfg_cluster_name,	/* var_name */
		NULL					/* default value */
	},
	{
		{
			(const char *)"conn_info",
			gettext_noop("connection info string"),
			NULL,
			SLON_C_STRING
		},
		&rtcfg_conninfo,
		NULL
	},
	{
		{
			(const char *)"pid_file",
			gettext_noop("Where to write the pid file"),
			NULL,
			SLON_C_STRING
		},
		&pid_file,
		NULL
	},
	{
		{
			(const char *)"log_timestamp_format",
			gettext_noop("A strftime()-style log timestamp format string."),
			NULL,
			SLON_C_STRING
		},
		&log_timestamp_format,
		"%Y-%m-%d %H:%M:%S %Z"
	},
	{
		{
			(const char *)"archive_dir",
			gettext_noop("Where to drop the sync archive files"),
			NULL,
			SLON_C_STRING
		},
		&archive_dir,
		NULL
	},
	{
		{
			(const char *)"sql_on_connection",
			gettext_noop("SQL to send to each connected node upon "
						 "connection establishment, useful to enable "
						 "duration logging, or to adjust any other "
						 "connection settable GUC"),
			NULL,
			SLON_C_STRING
		},
		&sql_on_connection,
		NULL
	},


	{
		{
			(const char *)"lag_interval",
			gettext_noop("A PostgreSQL value compatible with ::interval "
						 "which indicates how far behind this node should "
						 "lag its providers."),
			NULL,
			SLON_C_STRING
		},
		&lag_interval,
		NULL
	},



#ifdef HAVE_SYSLOG
	{
		{
			(const char *)"syslog_facility",
			gettext_noop("Sets the syslog \"facility\" to be used when syslog enabled."),
			gettext_noop("Valid values are LOCAL0, LOCAL1, LOCAL2, LOCAL3, "
						 "LOCAL4, LOCAL5, LOCAL6, LOCAL7."),
			SLON_C_STRING
		},
		&Syslog_facility,
		"LOCAL0"
	},
	{
		{
			(const char *)"syslog_ident",
			gettext_noop("Sets the program name used to identify slon messages in syslog."),
			NULL,
			SLON_C_STRING
		},
		&Syslog_ident,
		"slon"
	},
#endif
	{0}
};
#endif
/*
 * Local Variables:
 *	tab-width: 4
 *	c-indent-level: 4
 *	c-basic-offset: 4
 * End:
 */
