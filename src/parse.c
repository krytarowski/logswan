/*****************************************************************************/
/*                                                                           */
/* Logswan 1.03                                                              */
/* Copyright (c) 2015-2016, Frederic Cambus                                  */
/* http://www.logswan.org                                                    */
/*                                                                           */
/* Created:      2015-05-31                                                  */
/* Last Updated: 2016-01-01                                                  */
/*                                                                           */
/* Logswan is released under the BSD 3-Clause license.                       */
/* See LICENSE file for details.                                             */
/*                                                                           */
/*****************************************************************************/

#include <string.h>

#include "parse.h"

void parseDate(struct date* parsedDate, char *date) {
	parsedDate->day = strtok(date, "/");
	parsedDate->month = strtok(NULL, "/");
	parsedDate->year = strtok(NULL, ":");
	parsedDate->hour = strtok(NULL, ":");
	parsedDate->minute = strtok(NULL, ":");
	parsedDate->second = strtok(NULL, " ");
}

void parseLine(struct logLine* parsedLine, char *lineBuffer) {
	/* Remote host */
	parsedLine->remoteHost = strtok(lineBuffer, " ");

	/* User-identifier */
	strtok(NULL, " ");

	/* User ID */
	strtok(NULL, "[");

	/* Date */
	parsedLine->date = strtok(NULL, "]");

	/* Requested resource */
	strtok(NULL, "\"");
	parsedLine->request = strtok(NULL, "\"");

	/* HTTP status codes */
	parsedLine->statusCode = strtok(NULL, " ");

	/* Returned object size */
	parsedLine->objectSize = strtok(NULL, " \"");
}

void parseRequest(struct request* parsedRequest, char *request) {
	char *pch = strrchr(request, ' ');

	if (pch) {
		parsedRequest->protocol = pch + 1;
		parsedRequest->method = strtok(request, " ");
	}
}
