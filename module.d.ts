export interface MsdfConfigFlags {
  maxAngle?: number;
  imageWidth?: number;
  imageHeight?: number;
  range?: number;
  scale?: number;
  translationX?: number;
  translationY?: number;
}

export interface GlyphData {
  data: Uint8Array;
  width: number;
  height: number;
}
export interface GlyphDictonary {
  [Key: string]: GlyphData;
}

export function generateMSDF(
  fileBuffer: Buffer,
  chars: string,
  msdfCnfigFlags?: MsdfConfigFlags
): GlyphDictonary;
