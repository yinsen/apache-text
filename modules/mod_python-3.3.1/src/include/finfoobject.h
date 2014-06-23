/*
 * Copyright 2004 Apache Software Foundation 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License.  You
 * may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.  See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * Originally developed by Gregory Trubetskoy.
 *
 *
 * finfoobject.h 
 *
 * $Id: finfoobject.h 434388 2006-08-24 12:42:59Z grahamd $
 *
 */

#ifndef Mp_FINFOOBJECT_H
#define Mp_FINFOOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct finfoobject {
        PyObject_HEAD
        apr_pool_t      *pool;
        apr_finfo_t     *finfo;
    } finfoobject;

    extern DL_IMPORT(PyTypeObject) MpFinfo_Type;
    
#define MpFinfo_Check(op) ((op)->ob_type == &MpFinfo_Type)
    
    extern DL_IMPORT(PyObject *) MpFinfo_FromFinfo Py_PROTO((apr_finfo_t *f));
    extern DL_IMPORT(PyObject *) MpFinfo_New Py_PROTO((void));

#ifdef __cplusplus
}
#endif
#endif /* !Mp_FINFOOBJECT_H */
