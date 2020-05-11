import bindings from 'bindings';

// tslint:disable-next-line: no-any
const addon: any = bindings('decoder-utility');

// Creating and exporting persistent object for screen capture utility
// tslint:disable-next-line: no-unsafe-any export-name
export const decoderUtility: IDecoderUtility = new addon.DecoderUtility();

interface IDecoderUtility {
    /**
     * Initialises the x265 decoder
     */
    init(): void;

    /**
     * Returns the decoded frame buffer as a callback
     */
    decodeFrame(encodedFrame: ArrayBuffer, callback: (decodedFrame: IDecodedFrame) => void): void;
}

export interface IDecodedFrame {
    height: number;
    width: number;
    yData: ArrayBuffer;
    uData: ArrayBuffer;
    vData: ArrayBuffer;
}
