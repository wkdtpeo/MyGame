/*
 * Copyright (c) 2020 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "pas_config.h"

#if LIBPAS_ENABLED

#include "pas_race_test_hooks.h"

#if PAS_ENABLE_TESTING

pas_race_test_hook_callback pas_race_test_hook_callback_instance = NULL;
pas_race_test_lock_callback pas_race_test_will_lock_callback = NULL;
pas_race_test_lock_callback pas_race_test_did_lock_callback = NULL;
pas_race_test_lock_callback pas_race_test_did_try_lock_callback = NULL;
pas_race_test_lock_callback pas_race_test_will_unlock_callback = NULL;

void pas_race_test_hook(pas_race_test_hook_kind kind, ...)
{
    pas_race_test_hook_callback callback;
    callback = pas_race_test_hook_callback_instance;
    if (callback) {
        va_list arg_list;
        va_start(arg_list, kind);
        callback(kind, arg_list);
        va_end(arg_list);
    }
}

#endif /* PAS_ENABLE_TESTING */

#endif /* LIBPAS_ENABLED */
