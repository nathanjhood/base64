
export function hello(): string;
export function version(): string;
export function encode(string: string): string;
export function encode(string: string, urlMode: boolean): string;
export function decode(string: string): string;
export interface base64 {
  hello(): string;
  version(): string;
  encode(string: string): string;
  encode(string: string, urlMode: boolean): string;
  decode(string: string): string;
}
