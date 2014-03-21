





/*************************************************************************
	[1]~[3] phases.

***************************************************************************/
static void mobileserver_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(mobileserver_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(mobileserver_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_open_logs(mobileserver_open_logs, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(mobileserver_child_init, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_quick_handler(mobileserver_quick_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_connection(mobileserver_pre_connection, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_process_connection(mobileserver_process_connection, NULL, NULL, APR_HOOK_MIDDLE);


    /* [1] post read_request handling */
	/* General-purpose hook that runs immediately on creating the request_rec object*/
    ap_hook_post_read_request(mobileserver_post_read_request, NULL, NULL,
                              APR_HOOK_MIDDLE);
#if 0
    ap_hook_http_scheme(x_http_scheme, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_default_port(x_default_port, NULL, NULL, APR_HOOK_MIDDLE);
#endif

	/* [2] begin, collectively known as the request preparation phase */
	/* Map the request URL to the filesystem */
    ap_hook_translate_name(mobileserver_translate_handler, NULL, NULL, APR_HOOK_MIDDLE);

	/* Apply per-directory configuration */
    ap_hook_map_to_storage(mobileserver_map_to_storage_handler, NULL,NULL, APR_HOOK_MIDDLE);

	/* Check the HTTP request headers. Another general-purpose hook after the configuration 
	     is fully available but before more specific phases begin */
    ap_hook_header_parser(mobileserver_header_parser_handler, NULL, NULL, APR_HOOK_MIDDLE);

	/* Check whether access is permitted to the remote host */
    ap_hook_access_checker(mobileserver_access_checker, NULL, NULL, APR_HOOK_MIDDLE);

	/* Authenticate the remote user (where applicable) */
    ap_hook_check_user_id(mobileserver_check_user_id, NULL, NULL, APR_HOOK_MIDDLE);

	/* Check whether the remote user is authorized to perform the attempted operation */
    ap_hook_auth_checker(mobileserver_auth_checker, NULL, NULL, APR_HOOK_MIDDLE);

	/*Apply configuration rules that determine the handler and response headers*/
    ap_hook_type_checker(mobileserver_type_checker, NULL, NULL, APR_HOOK_MIDDLE);

	/* [2] end */
	/* General-purpose hook at the end of request preparation but before the handler is called */
    ap_hook_fixups(mobileserver_fixer_upper, NULL, NULL, APR_HOOK_MIDDLE);
	
	/* [3] begin, represent the handler (content generator) phase*/
    ap_hook_insert_filter(mobileserver_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);

	/* Handle the request and generate a response */
    ap_hook_handler(mobileserver_handler, NULL, NULL, APR_HOOK_MIDDLE);

	/* [3] end */
	/* Log the transaction */
    ap_hook_log_transaction(mobileserver_logger, NULL, NULL, APR_HOOK_MIDDLE);


}






static const command_rec mobileserver_cmds[] =
{
    AP_INIT_NO_ARGS(
        "Mobile",                          /* directive name */
        cmd_example,                        /* config action routine */
        NULL,                               /* argument to include in call */
        OR_OPTIONS,                         /* where available */
        "Example directive - no arguments"  /* directive description */
    ),
    {NULL}
};



module AP_MODULE_DECLARE_DATA mobileserver_module =
{
    STANDARD20_MODULE_STUFF,
    create_mobileserver_config,    /* per-directory config creator */
    merge_mobileserver_config,     /* dir config merger */
    create_mobileserver_config, /* server config creator */
    merge_mobileserver_config,  /* server config merger */
    mobileserver_cmds,                 /* command table */
    mobileserver_hooks,       /* set up other request processing hooks */
};
