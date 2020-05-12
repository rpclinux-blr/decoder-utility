import { decoderUtility, IDecodedFrame } from './index';

// decoderUtility.init();

const encFrame: ArrayBuffer = new Uint8Array(10).buffer;

decoderUtility.decodeFrame(encFrame, (decodedFrame: IDecodedFrame) => {
    //
});
