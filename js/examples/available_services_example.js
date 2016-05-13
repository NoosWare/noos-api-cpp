#!/usr/bin/env node

// Import the available_services JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.available_services = require('../includes/cloud/available_services.js');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.available_services
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
 
function handler ( services )
{
	console.log( "The following services are available:\n" );
	for (i = 0; i < services.length; i++) {
    	console.log(services[i]);
	}
}

services.available_services( handler );