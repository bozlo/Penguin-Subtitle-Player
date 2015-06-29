/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsSBCharSetProber.h"

static const unsigned char czech_iso_8859_2CharToOrderMap[] = 
{
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255, 32, 42, 49, 41, 63, 52, 36, 38, 53, 35, 37, 59, 44, 34, 47,
 33,180, 48, 45, 40, 56, 39, 76, 70, 75, 51,255,255,255,255,255,
255,  3, 24, 19, 11,  1, 50, 57, 17,  8, 16, 12,  5, 10,  4,  2,
 14, 58, 15,  6,  7, 13,  9, 80, 62, 21, 23,255,255,255,255,255,
179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,
163,162,161,160,159,158,157,156,155,154,153,152,151,150,149,148,
147,146,145,144,143,142,141,140,139, 64,138, 79,137,136, 61,135,
134,133,132,131,130,129,128,127,126, 28,125, 43,124,123, 25,122,
121, 71,120,119,118,117,116,115, 60, 72,114,113, 73, 69,112, 78,
111,110,109, 68,108,107,106,105, 65, 77, 67,104,103, 74,102,101,
100, 20, 99, 98, 97, 96, 95, 94, 27, 29, 93, 92, 22, 18, 91, 55,
 90, 89, 54, 66, 88, 87, 86, 85, 26, 31, 46, 84, 83, 30, 82, 81,
};

static const PRUint8 czechLangModel[] = 
{
1,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,1,0,0,3,3,3,3,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,2,0,0,0,2,2,0,2,0,0,0,0,2,0,0,
1,2,0,3,3,3,3,2,3,3,3,3,3,3,3,3,3,0,3,0,0,0,3,3,3,3,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,2,2,0,2,0,0,0,0,0,0,0,
1,2,1,3,3,3,3,2,3,3,3,3,2,3,3,3,3,0,3,0,0,0,3,3,3,3,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,2,2,0,2,0,0,0,0,0,0,0,
3,3,3,3,2,3,3,3,0,0,3,3,3,0,0,0,2,3,3,3,3,3,2,2,3,0,2,2,3,3,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,
3,3,3,3,3,3,2,3,2,2,2,3,3,0,0,3,2,3,2,3,3,0,3,2,2,0,3,2,3,3,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,
3,3,3,3,3,2,3,3,3,3,2,3,3,3,3,2,2,3,3,3,3,1,0,2,0,0,1,0,1,2,2,0,
0,0,0,0,0,0,0,0,0,0,3,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,2,2,3,3,2,2,3,3,0,3,0,2,3,2,3,3,3,1,2,0,3,2,2,3,3,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,2,2,3,3,3,3,2,3,3,3,3,2,3,2,3,3,2,3,2,0,0,3,3,3,1,3,3,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,0,0,2,2,0,2,0,0,0,0,0,0,0,
3,3,3,3,3,3,2,3,0,1,3,2,3,2,3,2,2,3,2,3,3,3,3,2,3,3,3,3,3,3,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,3,2,3,0,0,2,2,3,2,3,0,2,3,2,3,3,3,0,2,3,2,2,1,3,3,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,3,2,3,3,2,2,3,3,3,3,2,2,3,3,3,3,3,0,3,2,3,2,3,3,3,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,3,3,3,3,2,3,2,3,0,3,0,2,0,2,3,3,0,0,0,2,3,1,0,3,3,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,2,3,3,3,3,3,3,3,3,3,0,3,3,3,3,0,3,0,0,0,3,3,3,2,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,3,0,0,0,2,2,0,0,0,0,0,0,0,0,0,
3,3,3,2,3,3,3,3,0,0,0,2,3,2,3,2,0,3,2,3,2,3,0,0,0,3,1,2,2,2,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
3,3,3,3,2,2,3,3,3,2,3,2,3,3,2,1,3,0,3,3,3,0,3,2,3,0,2,3,3,3,3,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,
3,2,3,3,3,3,3,3,2,3,3,2,3,2,2,0,2,3,2,3,0,0,2,2,2,1,2,3,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,2,3,2,3,2,2,2,3,0,3,0,0,0,3,3,3,1,0,2,2,2,1,0,3,3,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,3,3,3,3,0,3,3,3,3,0,2,3,3,3,0,3,0,0,0,3,3,3,2,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
3,3,2,3,2,0,3,3,2,2,0,3,2,2,0,1,3,3,0,1,1,0,0,0,0,0,0,0,1,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
0,0,0,3,3,3,3,0,3,3,3,3,0,3,3,2,3,0,3,2,0,0,3,2,3,3,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,0,3,3,3,3,0,2,2,3,3,2,3,2,2,3,0,3,0,0,0,2,3,3,2,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,
0,0,0,3,3,3,3,0,3,3,3,3,0,2,2,3,3,0,3,0,0,0,2,2,3,2,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,2,3,3,2,3,3,0,2,3,0,3,2,2,0,2,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,3,3,3,3,2,2,3,2,2,2,2,3,0,3,2,0,3,2,3,3,3,1,0,0,3,0,2,2,3,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,2,2,3,2,2,2,3,2,0,3,3,2,0,2,0,0,3,2,3,0,0,0,2,0,0,0,2,2,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
3,2,3,2,2,2,2,3,1,2,0,2,2,2,0,0,0,3,1,3,0,0,0,2,0,0,2,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,2,3,3,3,0,3,3,0,1,0,3,2,1,1,0,0,3,2,3,0,0,0,0,0,0,0,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,2,3,3,3,1,3,3,2,1,0,3,2,3,2,0,0,3,2,2,0,0,0,0,0,0,2,2,2,0,1,0,
0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
0,0,0,3,2,2,3,0,2,3,3,2,0,2,2,2,3,0,2,0,0,0,2,2,2,2,2,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,2,3,0,3,3,2,2,0,2,2,2,2,0,3,0,0,0,2,2,2,2,2,2,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,1,3,3,2,0,2,3,2,2,0,1,2,3,2,0,0,0,0,0,2,2,3,2,2,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,
0,0,0,3,3,2,0,0,2,2,2,0,0,2,2,0,2,0,2,1,0,0,0,2,2,0,2,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,3,3,0,2,2,2,2,0,0,0,0,2,0,3,0,0,2,0,2,0,2,0,0,0,3,0,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,2,3,0,0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,3,2,2,0,0,0,0,0,0,2,0,0,2,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
3,2,3,0,0,2,0,2,0,2,2,0,1,0,0,0,0,2,0,3,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,3,3,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,3,2,2,2,0,2,0,0,0,3,0,2,0,3,0,0,0,0,3,0,0,0,0,0,2,0,0,0,0,0,2,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,2,3,2,2,0,0,0,0,2,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,0,2,2,1,2,0,0,1,0,0,0,2,0,0,2,0,2,3,2,2,0,2,0,1,3,0,2,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,
2,3,3,0,0,0,0,2,2,1,0,0,3,0,2,0,0,2,0,0,2,2,0,0,0,2,0,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,3,2,2,2,0,0,2,2,0,0,0,2,0,3,0,0,2,0,2,2,2,0,0,0,2,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
2,3,2,0,1,0,0,1,0,0,0,0,3,0,2,0,0,1,0,2,3,2,0,0,0,0,0,0,0,2,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,3,0,0,0,2,0,0,0,0,0,2,0,0,3,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,3,2,2,0,0,3,0,0,0,0,2,0,2,0,0,2,0,2,2,2,0,0,0,0,0,0,2,0,2,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,2,2,1,3,2,2,2,0,2,2,2,2,0,0,0,2,2,2,2,0,2,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,2,2,3,2,0,1,2,2,2,0,3,2,2,2,0,2,0,0,0,2,0,2,3,2,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,2,2,2,2,0,2,0,2,2,0,2,0,0,2,0,2,0,0,0,2,2,0,0,2,0,0,0,0,0,
1,1,1,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,3,2,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
2,3,0,0,0,0,2,1,1,0,0,0,0,0,0,0,3,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,3,0,2,0,1,3,0,0,0,0,1,0,2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,3,2,2,0,1,0,2,2,2,2,0,2,2,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,3,0,0,0,0,3,0,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,
0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,1,0,0,0,0,
0,2,2,0,0,2,2,0,0,0,0,2,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,2,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,2,2,2,2,0,2,2,2,2,0,2,0,0,0,0,1,0,0,0,0,2,2,0,2,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,2,1,0,0,2,0,0,2,0,2,0,2,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,2,0,2,0,2,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,
2,0,2,0,2,0,1,1,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const SequenceModel iso_8859_2czechModel = 
{
  czech_iso_8859_2CharToOrderMap,
  czechLangModel,
  (float)0.968107,
  PR_TRUE,
  "iso-8859-2",
  "czech"
};
