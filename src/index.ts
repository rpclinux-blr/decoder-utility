import bindings from 'bindings';

// tslint:disable-next-line: no-any
const addon: any = bindings('decoder-utility');

// Creating and exporting persistent object for screen capture utility
// tslint:disable-next-line: no-unsafe-any export-name
export const decoderUtility: IDecoderUtility = new addon.DeecoderUtility();

interface IDecoderUtility {
    /**
     * Initialises the x265 decoder
     */
    init(width: number, height: number): void;

    /**
     * Returns the decoded frame buffer as a callback
     */
    decodeFrame(callback: (nextFrame: ArrayBuffer) => void): void;
}
