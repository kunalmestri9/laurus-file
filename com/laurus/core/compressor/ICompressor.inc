<?php

import('com.laurus.core.compressor.ICompressrorTypes');

/**
 * This Interface defines All the CompressorTypes Required.
 * If want to add new Compressor Type Just add another Type name and assign  int value to it.
 * @author Kunal Mestri
 * 
 */
interface ICompressor{
   /**
    * @return ICompressorType::ItemType
    */
    public  function getCompressorType();
    
}

?>
