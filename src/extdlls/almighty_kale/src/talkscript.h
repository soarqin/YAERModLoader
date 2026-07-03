/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void ak_setup_talkscript(void);
void ak_unhook_talkscript(void);

#ifdef __cplusplus
}
#endif