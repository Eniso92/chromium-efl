/*
 * Copyright (C) 2013 Samsung Electronics
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "chromium_glue.h"

// utility macros for type casting
#include <stdio.h>
#include <cassert>

#define GLUE_NOTALLOWED(msg) \
  fprintf(stderr, "[GLUE ERROR] %s: %s\n", __PRETTY_FUNCTION__, ""#msg); \
  assert(0);\

#define GLUE_CAST_START(type) \
  switch ((type)) {\

#define GLUE_CAST_TO(ewk_value, chromium_value) \
    case ewk_value: return chromium_value;

#define GLUE_CAST_FROM(ewk_value, chromium_value) \
    case chromium_value: return ewk_value;

#define GLUE_CAST_END() \
    default: \
      GLUE_NOTALLOWED("Invalid EWK<->Chromium type conversion")\
  }\

// early return chromium's null value if argval is ewk's null.
// initialize result to chromium's null value otherwise.
#define GLUE_SET_FLAG_TO_INIT(result, argval, ewk_null_value, chromium_null_value)\
  if (argval == (ewk_null_value))\
    return chromium_null_value;\
  int result = (chromium_null_value);

#define GLUE_SET_FLAG_FROM_INIT(result, argval, ewk_null_value, chromium_null_value)\
  if (argval == (chromium_null_value))\
    return ewk_null_value;\
  int result = (ewk_null_value);

// turn on chromium_flag in result if (argval & ewk_flag) is true
#define GLUE_SET_FLAG_TO(result, argval, ewk_flag, chromium_flag) \
  if ((argval) & (ewk_flag))\
    result |= (chromium_flag);

// turn on ewk_flag in result if (argval & chromium_flag) is true
#define GLUE_SET_FLAG_FROM(result, argval, ewk_flag, chromium_flag) \
  if ((argval) & (chromium_flag))\
    result |= (ewk_flag);


namespace chromium_glue {

// To access enum values without namespace
using namespace tizen_webview;

tw::Cache_Model to(Ewk_Cache_Model val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO (EWK_CACHE_MODEL_DOCUMENT_VIEWER, TW_CACHE_MODEL_DOCUMENT_VIEWER)
    GLUE_CAST_TO (EWK_CACHE_MODEL_DOCUMENT_BROWSER, TW_CACHE_MODEL_DOCUMENT_BROWSER)
    GLUE_CAST_TO (EWK_CACHE_MODEL_PRIMARY_WEBBROWSER, TW_CACHE_MODEL_PRIMARY_WEBBROWSER)
  GLUE_CAST_END()
}

Ewk_Cache_Model from(tw::Cache_Model val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_CACHE_MODEL_DOCUMENT_VIEWER, TW_CACHE_MODEL_DOCUMENT_VIEWER)
    GLUE_CAST_FROM(EWK_CACHE_MODEL_DOCUMENT_BROWSER, TW_CACHE_MODEL_DOCUMENT_BROWSER)
    GLUE_CAST_FROM(EWK_CACHE_MODEL_PRIMARY_WEBBROWSER, TW_CACHE_MODEL_PRIMARY_WEBBROWSER)
  GLUE_CAST_END()
}

tw::Cookie_Accept_Policy to(Ewk_Cookie_Accept_Policy val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_COOKIE_ACCEPT_POLICY_ALWAYS, TW_COOKIE_ACCEPT_POLICY_ALWAYS)
    GLUE_CAST_TO(EWK_COOKIE_ACCEPT_POLICY_NEVER, TW_COOKIE_ACCEPT_POLICY_NEVER)
    GLUE_CAST_TO(EWK_COOKIE_ACCEPT_POLICY_NO_THIRD_PARTY, TW_COOKIE_ACCEPT_POLICY_NO_THIRD_PARTY)
  GLUE_CAST_END()
}

Ewk_Cookie_Accept_Policy from(tw::Cookie_Accept_Policy val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_COOKIE_ACCEPT_POLICY_ALWAYS, TW_COOKIE_ACCEPT_POLICY_ALWAYS)
    GLUE_CAST_FROM(EWK_COOKIE_ACCEPT_POLICY_NEVER, TW_COOKIE_ACCEPT_POLICY_NEVER)
    GLUE_CAST_FROM(EWK_COOKIE_ACCEPT_POLICY_NO_THIRD_PARTY, TW_COOKIE_ACCEPT_POLICY_NO_THIRD_PARTY)
  GLUE_CAST_END()
}

tw::Legacy_Font_Size_Mode to(Ewk_Legacy_Font_Size_Mode val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_LEGACY_FONT_SIZE_MODE_ALWAYS, TW_LEGACY_FONT_SIZE_MODE_ALWAYS)
    GLUE_CAST_TO(EWK_LEGACY_FONT_SIZE_MODE_ONLY_IF_PIXEL_VALUES_MATCH, TW_LEGACY_FONT_SIZE_MODE_ONLY_IF_PIXEL_VALUES_MATCH)
    GLUE_CAST_TO(EWK_LEGACY_FONT_SIZE_MODE_NEVER, TW_LEGACY_FONT_SIZE_MODE_NEVER)
  GLUE_CAST_END()
}

Ewk_Legacy_Font_Size_Mode from(tw::Legacy_Font_Size_Mode val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_LEGACY_FONT_SIZE_MODE_ALWAYS, TW_LEGACY_FONT_SIZE_MODE_ALWAYS)
    GLUE_CAST_FROM(EWK_LEGACY_FONT_SIZE_MODE_ONLY_IF_PIXEL_VALUES_MATCH, TW_LEGACY_FONT_SIZE_MODE_ONLY_IF_PIXEL_VALUES_MATCH)
    GLUE_CAST_FROM(EWK_LEGACY_FONT_SIZE_MODE_NEVER, TW_LEGACY_FONT_SIZE_MODE_NEVER)
  GLUE_CAST_END()
}

tw::Hit_Test_Result_Context to(Ewk_Hit_Test_Result_Context val)
{
  GLUE_SET_FLAG_TO_INIT(res, val, static_cast<Ewk_Hit_Test_Result_Context>(0), static_cast<tw::Hit_Test_Result_Context>(0))
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_DOCUMENT, TW_HIT_TEST_RESULT_CONTEXT_DOCUMENT)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_LINK, TW_HIT_TEST_RESULT_CONTEXT_LINK)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_IMAGE, TW_HIT_TEST_RESULT_CONTEXT_IMAGE)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_MEDIA, TW_HIT_TEST_RESULT_CONTEXT_MEDIA)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_SELECTION, TW_HIT_TEST_RESULT_CONTEXT_SELECTION)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_EDITABLE, TW_HIT_TEST_RESULT_CONTEXT_EDITABLE)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_RESULT_CONTEXT_TEXT, TW_HIT_TEST_RESULT_CONTEXT_TEXT)
  return static_cast<tw::Hit_Test_Result_Context>(res);
}

Ewk_Hit_Test_Result_Context from(tw::Hit_Test_Result_Context val)
{
  GLUE_SET_FLAG_FROM_INIT(res, val, static_cast<Ewk_Hit_Test_Result_Context>(0), static_cast<tw::Hit_Test_Result_Context>(0))
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_DOCUMENT, TW_HIT_TEST_RESULT_CONTEXT_DOCUMENT)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_LINK, TW_HIT_TEST_RESULT_CONTEXT_LINK)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_IMAGE, TW_HIT_TEST_RESULT_CONTEXT_IMAGE)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_MEDIA, TW_HIT_TEST_RESULT_CONTEXT_MEDIA)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_SELECTION, TW_HIT_TEST_RESULT_CONTEXT_SELECTION)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_EDITABLE, TW_HIT_TEST_RESULT_CONTEXT_EDITABLE)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_RESULT_CONTEXT_TEXT, TW_HIT_TEST_RESULT_CONTEXT_TEXT)
  return static_cast<Ewk_Hit_Test_Result_Context>(res);
}

tw::Hit_Test_Mode to(Ewk_Hit_Test_Mode val)
{
  GLUE_SET_FLAG_TO_INIT(res, val, static_cast<Ewk_Hit_Test_Mode>(0), static_cast<tw::Hit_Test_Mode>(0))
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_MODE_DEFAULT, TW_HIT_TEST_MODE_DEFAULT)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_MODE_NODE_DATA, TW_HIT_TEST_MODE_NODE_DATA)
  GLUE_SET_FLAG_TO(res, val, EWK_HIT_TEST_MODE_IMAGE_DATA, TW_HIT_TEST_MODE_IMAGE_DATA)
  return static_cast<tw::Hit_Test_Mode>(res);
}

Ewk_Hit_Test_Mode from(tw::Hit_Test_Mode val)
{
  GLUE_SET_FLAG_FROM_INIT(res, val, static_cast<Ewk_Hit_Test_Mode>(0), static_cast<tw::Hit_Test_Mode>(0))
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_MODE_DEFAULT, TW_HIT_TEST_MODE_DEFAULT)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_MODE_NODE_DATA, TW_HIT_TEST_MODE_NODE_DATA)
  GLUE_SET_FLAG_FROM(res, val, EWK_HIT_TEST_MODE_IMAGE_DATA, TW_HIT_TEST_MODE_IMAGE_DATA)
  return static_cast<Ewk_Hit_Test_Mode>(res);
}

tw::View_Hit_Test_Request_Callback to(Ewk_View_Hit_Test_Request_Callback callback)
{
  return reinterpret_cast<tw::View_Hit_Test_Request_Callback>(callback);
}

tw::Policy_Decision_Type to(Ewk_Policy_Decision_Type val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_POLICY_DECISION_USE, TW_POLICY_DECISION_USE)
    GLUE_CAST_TO(EWK_POLICY_DECISION_DOWNLOAD, TW_POLICY_DECISION_DOWNLOAD)
    GLUE_CAST_TO(EWK_POLICY_DECISION_IGNORE, TW_POLICY_DECISION_IGNORE)
  GLUE_CAST_END()
}

Ewk_Policy_Decision_Type from(tw::Policy_Decision_Type val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_POLICY_DECISION_USE, TW_POLICY_DECISION_USE)
    GLUE_CAST_FROM(EWK_POLICY_DECISION_DOWNLOAD, TW_POLICY_DECISION_DOWNLOAD)
    GLUE_CAST_FROM(EWK_POLICY_DECISION_IGNORE, TW_POLICY_DECISION_IGNORE)
  GLUE_CAST_END()
}

tw::Policy_Navigation_Type to(Ewk_Policy_Navigation_Type val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_POLICY_NAVIGATION_TYPE_LINK_CLICKED, TW_POLICY_NAVIGATION_TYPE_LINK_CLICKED)
    GLUE_CAST_TO(EWK_POLICY_NAVIGATION_TYPE_FORM_SUBMITTED, TW_POLICY_NAVIGATION_TYPE_FORM_SUBMITTED)
    GLUE_CAST_TO(EWK_POLICY_NAVIGATION_TYPE_BACK_FORWARD, TW_POLICY_NAVIGATION_TYPE_BACK_FORWARD)
    GLUE_CAST_TO(EWK_POLICY_NAVIGATION_TYPE_RELOAD, TW_POLICY_NAVIGATION_TYPE_RELOAD)
    GLUE_CAST_TO(EWK_POLICY_NAVIGATION_TYPE_FORM_RESUBMITTED, TW_POLICY_NAVIGATION_TYPE_FORM_RESUBMITTED)
    GLUE_CAST_TO(EWK_POLICY_NAVIGATION_TYPE_OTHER, TW_POLICY_NAVIGATION_TYPE_OTHER)
  GLUE_CAST_END()
}

Ewk_Policy_Navigation_Type from(tw::Policy_Navigation_Type val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_POLICY_NAVIGATION_TYPE_LINK_CLICKED, TW_POLICY_NAVIGATION_TYPE_LINK_CLICKED)
    GLUE_CAST_FROM(EWK_POLICY_NAVIGATION_TYPE_FORM_SUBMITTED, TW_POLICY_NAVIGATION_TYPE_FORM_SUBMITTED)
    GLUE_CAST_FROM(EWK_POLICY_NAVIGATION_TYPE_BACK_FORWARD, TW_POLICY_NAVIGATION_TYPE_BACK_FORWARD)
    GLUE_CAST_FROM(EWK_POLICY_NAVIGATION_TYPE_RELOAD, TW_POLICY_NAVIGATION_TYPE_RELOAD)
    GLUE_CAST_FROM(EWK_POLICY_NAVIGATION_TYPE_FORM_RESUBMITTED, TW_POLICY_NAVIGATION_TYPE_FORM_RESUBMITTED)
    GLUE_CAST_FROM(EWK_POLICY_NAVIGATION_TYPE_OTHER, TW_POLICY_NAVIGATION_TYPE_OTHER)
  GLUE_CAST_END()
}

tw::Touch_Event_Type to(Ewk_Touch_Event_Type val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_TOUCH_START, TW_TOUCH_START)
    GLUE_CAST_TO(EWK_TOUCH_MOVE, TW_TOUCH_MOVE)
    GLUE_CAST_TO(EWK_TOUCH_END, TW_TOUCH_END)
    GLUE_CAST_TO(EWK_TOUCH_CANCEL, TW_TOUCH_CANCEL)
  GLUE_CAST_END()
}

Ewk_Touch_Event_Type from(tw::Touch_Event_Type val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_TOUCH_START, TW_TOUCH_START)
    GLUE_CAST_FROM(EWK_TOUCH_MOVE, TW_TOUCH_MOVE)
    GLUE_CAST_FROM(EWK_TOUCH_END, TW_TOUCH_END)
    GLUE_CAST_FROM(EWK_TOUCH_CANCEL, TW_TOUCH_CANCEL)
  GLUE_CAST_END()
}

tw::Custom_Handlers_State to(Ewk_Custom_Handlers_State val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_CUSTOM_HANDLERS_NEW, TW_CUSTOM_HANDLERS_NEW)
    GLUE_CAST_TO(EWK_CUSTOM_HANDLERS_REGISTERED, TW_CUSTOM_HANDLERS_REGISTERED)
    GLUE_CAST_TO(EWK_CUSTOM_HANDLERS_DECLINED, TW_CUSTOM_HANDLERS_DECLINED)
  GLUE_CAST_END()
}


Ewk_Custom_Handlers_State from(tw::Custom_Handlers_State val)
{
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_CUSTOM_HANDLERS_NEW, TW_CUSTOM_HANDLERS_NEW)
    GLUE_CAST_FROM(EWK_CUSTOM_HANDLERS_REGISTERED, TW_CUSTOM_HANDLERS_REGISTERED)
    GLUE_CAST_FROM(EWK_CUSTOM_HANDLERS_DECLINED, TW_CUSTOM_HANDLERS_DECLINED)
  GLUE_CAST_END()
}

tw::Find_Options to(Ewk_Find_Options val)
{
  GLUE_SET_FLAG_TO_INIT(res, val, EWK_FIND_OPTIONS_NONE, TW_FIND_OPTIONS_NONE)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_CASE_INSENSITIVE, TW_FIND_OPTIONS_CASE_INSENSITIVE)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_BACKWARDS, TW_FIND_OPTIONS_BACKWARDS)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_AT_WORD_STARTS, TW_FIND_OPTIONS_AT_WORD_STARTS)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_TREAT_MEDIAL_CAPITAL_AS_WORD_START, TW_FIND_OPTIONS_TREAT_MEDIAL_CAPITAL_AS_WORD_START)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_WRAP_AROUND, TW_FIND_OPTIONS_WRAP_AROUND)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_SHOW_OVERLAY, TW_FIND_OPTIONS_SHOW_OVERLAY)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_SHOW_FIND_INDICATOR, TW_FIND_OPTIONS_SHOW_FIND_INDICATOR)
  GLUE_SET_FLAG_TO(res, val, EWK_FIND_OPTIONS_SHOW_HIGHLIGHT, TW_FIND_OPTIONS_SHOW_HIGHLIGHT)
  return static_cast<tw::Find_Options>(res);
}

Ewk_Find_Options from(tw::Find_Options val)
{
  GLUE_SET_FLAG_FROM_INIT(res, val, EWK_FIND_OPTIONS_NONE, TW_FIND_OPTIONS_NONE)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_CASE_INSENSITIVE, TW_FIND_OPTIONS_CASE_INSENSITIVE)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_BACKWARDS, TW_FIND_OPTIONS_BACKWARDS)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_AT_WORD_STARTS, TW_FIND_OPTIONS_AT_WORD_STARTS)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_TREAT_MEDIAL_CAPITAL_AS_WORD_START, TW_FIND_OPTIONS_TREAT_MEDIAL_CAPITAL_AS_WORD_START)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_WRAP_AROUND, TW_FIND_OPTIONS_WRAP_AROUND)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_SHOW_OVERLAY, TW_FIND_OPTIONS_SHOW_OVERLAY)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_SHOW_FIND_INDICATOR, TW_FIND_OPTIONS_SHOW_FIND_INDICATOR)
  GLUE_SET_FLAG_FROM(res, val, EWK_FIND_OPTIONS_SHOW_HIGHLIGHT, TW_FIND_OPTIONS_SHOW_HIGHLIGHT)
  return static_cast<Ewk_Find_Options>(res);
}

tw::ContentSecurityPolicyType to(Ewk_CSP_Header_Type val) {
  GLUE_CAST_START(val)
    GLUE_CAST_TO(EWK_REPORT_ONLY, TW_CSP_REPORT_ONLY)
    GLUE_CAST_TO(EWK_ENFORCE_POLICY, TW_CSP_ENFORCE_POLICY)
    GLUE_CAST_TO(EWK_DEFAULT_POLICY, TW_CSP_DEFAULT_POLICY)
  GLUE_CAST_END()
}

Ewk_CSP_Header_Type from(tw::ContentSecurityPolicyType val) {
  GLUE_CAST_START(val)
    GLUE_CAST_FROM(EWK_REPORT_ONLY, TW_CSP_REPORT_ONLY)
    GLUE_CAST_FROM(EWK_ENFORCE_POLICY, TW_CSP_ENFORCE_POLICY)
    GLUE_CAST_FROM(EWK_DEFAULT_POLICY, TW_CSP_DEFAULT_POLICY)
  GLUE_CAST_END()
}

} // namespace chromium_glue
