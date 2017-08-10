//
//  main.swift
//  apptestmac
//
//  Created by Michael Ong on 10/8/17.
//  Copyright © 2017 Michael Ong. All rights reserved.
//

import Foundation

import sushiapplication
import sushiwindow

Application.initialise  (with: macosApplicationDriver()) {

    _ = Application.instance.spawnWindow(logic: windowLogic2(), title: "Hello", at: .undefinedWindowLocation)
}

Application.destroy     ()
