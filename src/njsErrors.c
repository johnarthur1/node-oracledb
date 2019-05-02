// Copyright (c) 2015, 2019, Oracle and/or its affiliates. All rights reserved.

//-----------------------------------------------------------------------------
//
// You may not use the identified files except in compliance with the Apache
// License, Version 2.0 (the "License.")
//
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//
// See the License for the specific language governing permissions and
// limitations under the License.
//
// NAME
//   njsErrors.c
//
// DESCRIPTION
//   All error messages and the functions for getting them.
//
//-----------------------------------------------------------------------------

#include "njsModule.h"

static const char *njsErrorMessages[] = {
    "NJS-000: success",                              // errSuccess
    "NJS-001: expected callback as last parameter",  // errMissingCallback
    "NJS-002: invalid pool",                         // errInvalidPool
    "NJS-003: invalid connection",                   // errInvalidConnection
    "NJS-004: invalid value for property %s",        // errInvalidPropertyValue
    "NJS-005: invalid value for parameter %d",       // errInvalidParameterValue
    "NJS-007: invalid value for \"%s\" in parameter %d", // errInvalidPropertyValueInParam
    "NJS-009: invalid number of parameters",         // errInvalidNumberOfParameters
    "NJS-010: unsupported data type %d in column %u", // errUnsupportedDataType
    "NJS-011: encountered bind value and type mismatch", // errBindValueAndTypeMismatch
    "NJS-012: encountered invalid bind data type in parameter %d", // errInvalidBindDataType
    "NJS-013: invalid bind direction",               // errInvalidBindDirection
    "NJS-015: type was not specified for conversion", // errNoTypeForConversion
    "NJS-016: buffer is too small for OUT binds",    // errInsufficientBufferForBinds
    "NJS-017: concurrent operations on ResultSet are not allowed", // errBusyResultSet
    "NJS-018: invalid ResultSet",                   // errInvalidResultSet
    "NJS-019: ResultSet cannot be returned for non-query statements", // errInvalidNonQueryExecution
    "NJS-021: invalid type for conversion specified", // errInvalidTypeForConversion
    "NJS-022: invalid Lob",                           // errInvalidLob
    "NJS-023: concurrent operations on LOB are not allowed",  // errBusyLob
    "NJS-024: memory allocation failed",  // errInsufficientMemory
    "NJS-034: data type is unsupported for array bind", // errInvalidTypeForArrayBind
    "NJS-035: maxArraySize is required for IN OUT array bind", // errReqdMaxArraySize
    "NJS-036: given array is of size greater than maxArraySize", // errInvalidArraySize
    "NJS-037: invalid data type at array index %d for bind \":%.*s\"", // errIncompatibleTypeArrayBind
    "NJS-040: connection request timeout. Request exceeded queueTimeout of %d",  // errConnRequestTimeout
    "NJS-041: cannot convert ResultSet to QueryStream after invoking methods", // errCannotConvertRsToStream
    "NJS-042: cannot invoke ResultSet methods after converting to QueryStream", // errCannotInvokeRsMethods
    "NJS-043: ResultSet already converted to QueryStream", // errResultSetAlreadyConverted
    "NJS-044: named JSON object is not expected in this context", // errNamedJSON
    "NJS-045: cannot load a node-oracledb binary for Node.js %s", // errCannotLoadBinary
    "NJS-046: pool alias \"%s\" already exists in the connection pool cache", // errPoolWithAliasAlreadyExists
    "NJS-047: pool alias \"%s\" not found in connection pool cache", // errPoolWithAliasNotFound
    "NJS-052: invalid data type at array index %d for bind position %d", // errIncompatibleTypeArrayIndexBind
    "NJS-053: array value expected, a non-array value provided", //errNonArrayProvided
    "NJS-055: binding by position and name cannot be mixed", // errMixedBind
    "NJS-056: maxSize must be specified and not zero for bind position %u", // errMissingMaxSizeByPos
    "NJS-057: maxSize must be specified and not zero for bind \"%.*s\"", // errMissingMaxSizeByName
    "NJS-058: maxSize of %u is too small for value of length %u in row %u", // errMaxSizeTooSmall
    "NJS-059: type must be specified for bind position %u", // errMissingTypeByPos
    "NJS-060: type must be specified for bind \"%.*s\"", // errMissingTypeByName
    "NJS-061: invalid subscription", // errInvalidSubscription
    "NJS-062: subscription notification callback missing", // errMissingSubscrCallback
    "NJS-063: subscription notification SQL missing", // errMissingSubscrSql
    "NJS-064: connection pool is closing", // errPoolClosing
    "NJS-065: connection pool was closed", // errPoolClosed
    "NJS-066: invalid SODA document cursor", // errInvalidSodaDocCursor
    "NJS-067: a pre-built node-oracledb binary was not found for %s", // errNoBinaryAvailable
    "NJS-068: invalid error number %d supplied", // errInvalidErrNum
    "NJS-069: node-oracledb %s requires Node.js %s or later", // errNodeTooOld
};


//-----------------------------------------------------------------------------
// njsErrors_getMessage()
//   Get the error message given the error number and any number of arguments.
// If the error number is invalid, the error message is changed to indicate as
// much.
//-----------------------------------------------------------------------------
void njsErrors_getMessage(char *buffer, int errNum, ...)
{
    va_list vaList;

    va_start(vaList, errNum);
    njsErrors_getMessageVaList(buffer, errNum, vaList);
    va_end(vaList);
}


//-----------------------------------------------------------------------------
// njsErrors_getMessageVaList()
//   Get the error message given the error number and a variable list of
// arguments. If the error number is invalid, the error message is changed to
// indicate as much.
//-----------------------------------------------------------------------------
void njsErrors_getMessageVaList(char *buffer, int errNum, va_list vaList)
{
    if (errNum > 0 && errNum < errMaxErrors) {
        (void) vsnprintf(buffer, NJS_MAX_ERROR_MSG_LEN + 1,
                njsErrorMessages[errNum], vaList);
    } else {
        njsErrors_getMessage(buffer, errInvalidErrNum, errNum);
    }
}