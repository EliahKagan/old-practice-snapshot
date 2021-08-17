class GfG
{
    int wildCard(final String pattern, final String str)
    {
        return str.matches(pattern.replace('?', '.')
                                  .replaceAll("\\*+", ".*")) ? 1 : 0;
    }
}
