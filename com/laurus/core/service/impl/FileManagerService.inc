<?php
import("com.laurus.core.service.api.IFileManagerService");
import("com.laurus.core.util.TUtilString");
import("com.laurus.core.file.FileException");
import("com.laurus.core.service.ServiceException");
/**
 * Description of FileManagerService
 *
 * @author kunal.mestri
 */
class FileManagerService implements IFileManagerService {
    protected $initPath;
    protected $defaultDirectoryMode;
    public function init($config) {
        $this->defaultDirectoryMode=777;
        $this->initPath=$this->loadMandatoryConfiguration(IFileManagerService::FILER_CONFIGURATION_PATH, $config);
        if(!$this->isStoragePathExists()){
            $this->createFileStoragePath();
        }
    }
    
    public function isStoragePathExists() {
        return (file_exists($this->initPath));
    }
    protected function loadMandatoryConfiguration($paramterName,$config){
        $val = $config[$paramterName];
        if(!TUtilString::isValidString($val)){
            throw new FileException( $paramterName . "is not configured",  FileException_SUBTYPE::INCORRECT_CONFIGURATION);
        }
        return $val;
    }
    
    
    public function createFileStoragePath() {
        if(!$this->createFolder($folderName)){
            throw new ServiceException("Service could not be started",  ServiceException_SUBTYPE::SERVICE_INIT_FAILED);
        }
    }

    public function createFolder($folderName) {
        return $this->createFile($folderName,FILETYPE::DIRECTORY);
    }

    public function deleteFile($pathOfFile) {
         
    }
    protected function getPath($filepath){
        return $this->initPath . $filepath;
    }
    
    /**
     * 
     * @param FileType $type
     * @param String $filepath
     */
    public function createFile($filepath,$type=FILETYPE::FILE) {
        $actFilePath=$this->getPath($filepath);
        if($type==FILETYPE::FILE){
            if(!file_exists($actFilePath)){
                return fopen($actFilePath, 'w');
            }else{
                throw new FileException($actFilePath . " :: Already Exists ",FileException_SUBTYPE::FILE_ALREADY_EXSISTS);
            }
        }else if($type==FILETYPE::DIRECTORY){
            return mkdir($actFilePath, $this->defaultDirectoryMode, true);
        }
    }
}

?>
