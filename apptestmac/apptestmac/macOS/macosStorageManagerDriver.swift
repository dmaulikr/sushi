//
//  macosStorageManagerDriver.swift
//  apptestmac
//
//  Created by Michael Ong on 10/8/17.
//  Copyright © 2017 Michael Ong. All rights reserved.
//

import Foundation

import sushicore
import sushistorage

class macosStorageEntryDirectory: StorageEntryDirectory {

    var         url         : URL = URL(fileURLWithPath: "")

    var         children    : [StorageEntry]? {

        return try? FileManager.default
            .contentsOfDirectory    (at: url, includingPropertiesForKeys: nil, options: .skipsHiddenFiles)
            .map                    ({ url -> StorageEntry in

                var isDirectory: ObjCBool = false

                if FileManager.default.fileExists(atPath: url.path, isDirectory: &isDirectory) {

                    if isDirectory.boolValue {

                        let     directory       = macosStorageEntryDirectory()
                        directory.url   = url

                        return  directory
                    }
                    else {

                        let     file            = macosStorageEntryFile()
                        file.url        = url

                        return  file
                    }
                }
                else {

                    FastFail.instance.crash(with: FastFailType.unexpectedPayload)
                }
            })
    }


    func        contains    (_ relativeURL: String) -> Bool {

        return FileManager.default.fileExists(atPath: url.appendingPathComponent(relativeURL).path)
    }

    func        open        (_ relativeURL: String) -> StorageEntry? {

        var isDirectory: ObjCBool   = false
        let toOpen                  = url.appendingPathComponent(relativeURL)

        if FileManager.default.fileExists(atPath: toOpen.path, isDirectory: &isDirectory) {

            if isDirectory.boolValue {

                let     directory       = macosStorageEntryDirectory()
                directory.url   = toOpen

                return  directory
            }
            else {

                let     file            = macosStorageEntryFile()
                file.url        = toOpen

                return  file
            }
        }
        else {

            return nil
        }
    }

    func        create      (_ relativeURL: String) -> StorageEntry? {

        return nil
    }
}

class macosStorageEntryFile: StorageEntryFile {

    var         isReadOnly  : Bool  = true

    var         url         : URL   = URL(fileURLWithPath: "")


    func        dataStream  () -> Data? {

        return try? Data.init(contentsOf: url)
    }
}


class macosStorageManagerDriver: StorageManagerDriver {

    func        open        (from storageLocation: StorageManagerLocation) -> StorageEntryDirectory? {

        let     directory = macosStorageEntryDirectory()

        switch storageLocation {

        case .staging:      directory.url   = URL(fileURLWithPath: NSHomeDirectory(),       isDirectory: true)
        case .temporary:    directory.url   = URL(fileURLWithPath: NSTemporaryDirectory(),  isDirectory: true)
        case .local:        directory.url   = Bundle.main.resourceURL!

        default:            return  nil
        }

        return  directory
    }
}
