<?php
/**
 *
 * @author kunal.mestri
 */
interface IFileManagerService {
    const FILER_CONFIGURATION_PATH="FILER_CONFIGURATION_PATH";
    public function init($config);
    public function createFileStoragePath();
    public function createFolder($folderName);
    public function createFile($filepath,$type);
    public function deleteFile($pathOfFile);
    public function isStoragePathExists();
}

class FILETYPE{
    const DIRECTORY=0;
    const FILE=1;
}

?>
