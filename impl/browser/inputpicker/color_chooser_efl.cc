/*
    Copyright (C) 2014 Samsung Electronics

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "color_chooser_efl.h"
#include "base/logging.h"
#include "web_contents_delegate_efl.h"

namespace content {

ColorChooserEfl::ColorChooserEfl(WebContents* web_contents)
    : web_contents_delegate_(0) {
  SetWebContentsDelegateEfl(web_contents);
}

ColorChooserEfl::~ColorChooserEfl() {
}

void ColorChooserEfl::SetSelectedColor(SkColor color) {
  web_contents_delegate_->web_contents()->DidChooseColorInColorChooser(color);
}

void ColorChooserEfl::End() {
  web_contents_delegate_->web_contents()->DidEndColorChooser();
}

void ColorChooserEfl::SetWebContentsDelegateEfl(WebContents* web_contents) {
  web_contents_delegate_ = static_cast<WebContentsDelegateEfl*>(web_contents->GetDelegate());
}
}